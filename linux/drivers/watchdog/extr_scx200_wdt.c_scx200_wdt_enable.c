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

/* Variables and functions */
 scalar_t__ SCx200_WDT_WDCNFG ; 
 scalar_t__ SCx200_WDT_WDSTS ; 
 int /*<<< orphan*/  SCx200_WDT_WDSTS_WDOVF ; 
 scalar_t__ SCx200_WDT_WDTO ; 
 int /*<<< orphan*/  W_ENABLE ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ scx200_cb_base ; 
 int /*<<< orphan*/  scx200_wdt_ping () ; 
 int /*<<< orphan*/  scx_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdto_restart ; 

__attribute__((used)) static void scx200_wdt_enable(void)
{
	pr_debug("enabling watchdog timer, wdto_restart = %d\n", wdto_restart);

	spin_lock(&scx_lock);
	outw(0, scx200_cb_base + SCx200_WDT_WDTO);
	outb(SCx200_WDT_WDSTS_WDOVF, scx200_cb_base + SCx200_WDT_WDSTS);
	outw(W_ENABLE, scx200_cb_base + SCx200_WDT_WDCNFG);
	spin_unlock(&scx_lock);

	scx200_wdt_ping();
}