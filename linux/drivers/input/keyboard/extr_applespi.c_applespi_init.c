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
struct applespi_data {int want_mt_init_cmd; int want_tp_info_cmd; int /*<<< orphan*/  cmd_msg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  applespi_send_cmd_msg (struct applespi_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void applespi_init(struct applespi_data *applespi, bool is_resume)
{
	unsigned long flags;

	spin_lock_irqsave(&applespi->cmd_msg_lock, flags);

	if (is_resume)
		applespi->want_mt_init_cmd = true;
	else
		applespi->want_tp_info_cmd = true;
	applespi_send_cmd_msg(applespi);

	spin_unlock_irqrestore(&applespi->cmd_msg_lock, flags);
}