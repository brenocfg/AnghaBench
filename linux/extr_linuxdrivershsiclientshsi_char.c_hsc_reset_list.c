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
struct hsc_channel {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsc_free_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  list_splice_init (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hsc_reset_list(struct hsc_channel *channel, struct list_head *l)
{
	unsigned long flags;
	LIST_HEAD(list);

	spin_lock_irqsave(&channel->lock, flags);
	list_splice_init(l, &list);
	spin_unlock_irqrestore(&channel->lock, flags);

	hsc_free_list(&list);
}