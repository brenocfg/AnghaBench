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
struct applespi_data {int read_active; int write_active; int cmd_msg_queued; int /*<<< orphan*/  cmd_msg_lock; int /*<<< orphan*/  drain_complete; scalar_t__ drain; } ;

/* Variables and functions */
 int /*<<< orphan*/  applespi_send_cmd_msg (struct applespi_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void applespi_msg_complete(struct applespi_data *applespi,
				  bool is_write_msg, bool is_read_compl)
{
	unsigned long flags;

	spin_lock_irqsave(&applespi->cmd_msg_lock, flags);

	if (is_read_compl)
		applespi->read_active = false;
	if (is_write_msg)
		applespi->write_active = false;

	if (applespi->drain && !applespi->write_active)
		wake_up_all(&applespi->drain_complete);

	if (is_write_msg) {
		applespi->cmd_msg_queued = false;
		applespi_send_cmd_msg(applespi);
	}

	spin_unlock_irqrestore(&applespi->cmd_msg_lock, flags);
}