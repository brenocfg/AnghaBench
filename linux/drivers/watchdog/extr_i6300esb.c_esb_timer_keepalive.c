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
struct esb_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESB_RELOAD_REG (struct esb_dev*) ; 
 int /*<<< orphan*/  ESB_WDT_RELOAD ; 
 int /*<<< orphan*/  esb_unlock_registers (struct esb_dev*) ; 
 struct esb_dev* to_esb_dev (struct watchdog_device*) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esb_timer_keepalive(struct watchdog_device *wdd)
{
	struct esb_dev *edev = to_esb_dev(wdd);

	esb_unlock_registers(edev);
	writew(ESB_WDT_RELOAD, ESB_RELOAD_REG(edev));
	/* FIXME: Do we need to flush anything here? */
	return 0;
}