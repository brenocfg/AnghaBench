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
struct list_head {int dummy; } ;
struct hsi_msg {int /*<<< orphan*/  link; } ;
struct hsc_channel {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hsc_add_tail(struct hsc_channel *channel, struct hsi_msg *msg,
							struct list_head *queue)
{
	unsigned long flags;

	spin_lock_irqsave(&channel->lock, flags);
	list_add_tail(&msg->link, queue);
	spin_unlock_irqrestore(&channel->lock, flags);
}