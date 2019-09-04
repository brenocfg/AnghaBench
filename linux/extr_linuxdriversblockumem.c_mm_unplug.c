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
struct cardinfo {int /*<<< orphan*/  lock; } ;
struct blk_plug_cb {struct cardinfo* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  activate (struct cardinfo*) ; 
 int /*<<< orphan*/  kfree (struct blk_plug_cb*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mm_unplug(struct blk_plug_cb *cb, bool from_schedule)
{
	struct cardinfo *card = cb->data;

	spin_lock_irq(&card->lock);
	activate(card);
	spin_unlock_irq(&card->lock);
	kfree(cb);
}