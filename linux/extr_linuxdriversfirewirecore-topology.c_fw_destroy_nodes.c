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
struct fw_card {int /*<<< orphan*/  lock; int /*<<< orphan*/ * local_node; int /*<<< orphan*/  color; } ;

/* Variables and functions */
 int /*<<< orphan*/  for_each_fw_node (struct fw_card*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_lost_node ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void fw_destroy_nodes(struct fw_card *card)
{
	unsigned long flags;

	spin_lock_irqsave(&card->lock, flags);
	card->color++;
	if (card->local_node != NULL)
		for_each_fw_node(card, card->local_node, report_lost_node);
	card->local_node = NULL;
	spin_unlock_irqrestore(&card->lock, flags);
}