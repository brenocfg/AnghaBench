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
struct applespi_data {int want_cl_led_on; int /*<<< orphan*/  cmd_msg_lock; } ;

/* Variables and functions */
 int applespi_send_cmd_msg (struct applespi_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int applespi_set_capsl_led(struct applespi_data *applespi,
				  bool capslock_on)
{
	unsigned long flags;
	int sts;

	spin_lock_irqsave(&applespi->cmd_msg_lock, flags);

	applespi->want_cl_led_on = capslock_on;
	sts = applespi_send_cmd_msg(applespi);

	spin_unlock_irqrestore(&applespi->cmd_msg_lock, flags);

	return sts;
}