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
struct ipmi_recv_msg {int /*<<< orphan*/  link; } ;
struct ipmi_file_private {int /*<<< orphan*/  fasync_queue; int /*<<< orphan*/  wait; int /*<<< orphan*/  recv_msg_lock; int /*<<< orphan*/  recv_msgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void file_receive_handler(struct ipmi_recv_msg *msg,
				 void                 *handler_data)
{
	struct ipmi_file_private *priv = handler_data;
	int                      was_empty;
	unsigned long            flags;

	spin_lock_irqsave(&priv->recv_msg_lock, flags);
	was_empty = list_empty(&priv->recv_msgs);
	list_add_tail(&msg->link, &priv->recv_msgs);
	spin_unlock_irqrestore(&priv->recv_msg_lock, flags);

	if (was_empty) {
		wake_up_interruptible(&priv->wait);
		kill_fasync(&priv->fasync_queue, SIGIO, POLL_IN);
	}
}