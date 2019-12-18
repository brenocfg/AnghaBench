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
struct clone {int /*<<< orphan*/  lock; int /*<<< orphan*/  deferred_bios; } ;
struct bio_list {int dummy; } ;

/* Variables and functions */
 struct bio_list BIO_EMPTY_LIST ; 
 scalar_t__ bio_list_empty (struct bio_list*) ; 
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_list_merge (struct bio_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  submit_bios (struct bio_list*) ; 

__attribute__((used)) static void process_deferred_bios(struct clone *clone)
{
	unsigned long flags;
	struct bio_list bios = BIO_EMPTY_LIST;

	spin_lock_irqsave(&clone->lock, flags);
	bio_list_merge(&bios, &clone->deferred_bios);
	bio_list_init(&clone->deferred_bios);
	spin_unlock_irqrestore(&clone->lock, flags);

	if (bio_list_empty(&bios))
		return;

	submit_bios(&bios);
}