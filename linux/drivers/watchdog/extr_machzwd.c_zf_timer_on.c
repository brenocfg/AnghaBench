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
 int /*<<< orphan*/  PULSE_LEN ; 
 int /*<<< orphan*/  WD1 ; 
 int /*<<< orphan*/  ZF_CTIMEOUT ; 
 scalar_t__ ZF_HW_TIMEO ; 
 scalar_t__ ZF_USER_TIMEO ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ next_heartbeat ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int zf_action ; 
 unsigned int zf_get_control () ; 
 int /*<<< orphan*/  zf_port_lock ; 
 int /*<<< orphan*/  zf_set_control (unsigned int) ; 
 int /*<<< orphan*/  zf_set_timer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zf_timer ; 
 int /*<<< orphan*/  zf_writeb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void zf_timer_on(void)
{
	unsigned int ctrl_reg = 0;
	unsigned long flags;

	spin_lock_irqsave(&zf_port_lock, flags);

	zf_writeb(PULSE_LEN, 0xff);

	zf_set_timer(ZF_CTIMEOUT, WD1);

	/* user land ping */
	next_heartbeat = jiffies + ZF_USER_TIMEO;

	/* start the timer for internal ping */
	mod_timer(&zf_timer, jiffies + ZF_HW_TIMEO);

	/* start watchdog timer */
	ctrl_reg = zf_get_control();
	ctrl_reg |= (ENABLE_WD1|zf_action);
	zf_set_control(ctrl_reg);
	spin_unlock_irqrestore(&zf_port_lock, flags);

	pr_info("Watchdog timer is now enabled\n");
}