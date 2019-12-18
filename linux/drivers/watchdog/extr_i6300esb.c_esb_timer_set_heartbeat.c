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
typedef  unsigned int u32 ;
struct watchdog_device {unsigned int timeout; } ;
struct esb_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESB_RELOAD_REG (struct esb_dev*) ; 
 int /*<<< orphan*/  ESB_TIMER1_REG (struct esb_dev*) ; 
 int /*<<< orphan*/  ESB_TIMER2_REG (struct esb_dev*) ; 
 int /*<<< orphan*/  ESB_WDT_RELOAD ; 
 int /*<<< orphan*/  esb_unlock_registers (struct esb_dev*) ; 
 struct esb_dev* to_esb_dev (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int esb_timer_set_heartbeat(struct watchdog_device *wdd,
		unsigned int time)
{
	struct esb_dev *edev = to_esb_dev(wdd);
	u32 val;

	/* We shift by 9, so if we are passed a value of 1 sec,
	 * val will be 1 << 9 = 512, then write that to two
	 * timers => 2 * 512 = 1024 (which is decremented at 1KHz)
	 */
	val = time << 9;

	/* Write timer 1 */
	esb_unlock_registers(edev);
	writel(val, ESB_TIMER1_REG(edev));

	/* Write timer 2 */
	esb_unlock_registers(edev);
	writel(val, ESB_TIMER2_REG(edev));

	/* Reload */
	esb_unlock_registers(edev);
	writew(ESB_WDT_RELOAD, ESB_RELOAD_REG(edev));

	/* FIXME: Do we need to flush everything out? */

	/* Done */
	wdd->timeout = time;
	return 0;
}