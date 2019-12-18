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
struct lcs_card {unsigned long thread_allowed_mask; int /*<<< orphan*/  wait_q; int /*<<< orphan*/  mask_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lcs_set_allowed_threads(struct lcs_card *card, unsigned long threads)
{
	unsigned long flags;

	spin_lock_irqsave(&card->mask_lock, flags);
	card->thread_allowed_mask = threads;
	spin_unlock_irqrestore(&card->mask_lock, flags);
	wake_up(&card->wait_q);
}