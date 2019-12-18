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
 unsigned int ENABLE_WD1 ; 
 unsigned int ENABLE_WD2 ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int zf_get_control () ; 
 int /*<<< orphan*/  zf_port_lock ; 
 int /*<<< orphan*/  zf_set_control (unsigned int) ; 
 int /*<<< orphan*/  zf_timer ; 

__attribute__((used)) static void zf_timer_off(void)
{
	unsigned int ctrl_reg = 0;
	unsigned long flags;

	/* stop internal ping */
	del_timer_sync(&zf_timer);

	spin_lock_irqsave(&zf_port_lock, flags);
	/* stop watchdog timer */
	ctrl_reg = zf_get_control();
	ctrl_reg |= (ENABLE_WD1|ENABLE_WD2);	/* disable wd1 and wd2 */
	ctrl_reg &= ~(ENABLE_WD1|ENABLE_WD2);
	zf_set_control(ctrl_reg);
	spin_unlock_irqrestore(&zf_port_lock, flags);

	pr_info("Watchdog timer is now disabled\n");
}