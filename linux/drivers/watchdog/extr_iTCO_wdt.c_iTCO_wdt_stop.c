#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct watchdog_device {int dummy; } ;
struct iTCO_wdt_private {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  no_reboot_priv; int /*<<< orphan*/  (* update_no_reboot_bit ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  smi_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCO1_CNT (struct iTCO_wdt_private*) ; 
 int /*<<< orphan*/  iTCO_vendor_pre_stop (int /*<<< orphan*/ ) ; 
 unsigned int inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 struct iTCO_wdt_private* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int iTCO_wdt_stop(struct watchdog_device *wd_dev)
{
	struct iTCO_wdt_private *p = watchdog_get_drvdata(wd_dev);
	unsigned int val;

	spin_lock(&p->io_lock);

	iTCO_vendor_pre_stop(p->smi_res);

	/* Bit 11: TCO Timer Halt -> 1 = The TCO timer is disabled */
	val = inw(TCO1_CNT(p));
	val |= 0x0800;
	outw(val, TCO1_CNT(p));
	val = inw(TCO1_CNT(p));

	/* Set the NO_REBOOT bit to prevent later reboots, just for sure */
	p->update_no_reboot_bit(p->no_reboot_priv, true);

	spin_unlock(&p->io_lock);

	if ((val & 0x0800) == 0)
		return -1;
	return 0;
}