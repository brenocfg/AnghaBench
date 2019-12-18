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
struct clone {int /*<<< orphan*/  lock; int /*<<< orphan*/  deferred_flush_bios; int /*<<< orphan*/  deferred_bios; } ;
struct bio_list {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 struct bio_list BIO_EMPTY_LIST ; 
 int /*<<< orphan*/  bio_list_add (struct bio_list*,struct bio*) ; 
 scalar_t__ bio_list_empty (struct bio_list*) ; 
 int /*<<< orphan*/  bio_list_merge (int /*<<< orphan*/ *,struct bio_list*) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 
 scalar_t__ bio_triggers_commit (struct clone*,struct bio*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_worker (struct clone*) ; 

__attribute__((used)) static void issue_deferred_bios(struct clone *clone, struct bio_list *bios)
{
	struct bio *bio;
	unsigned long flags;
	struct bio_list flush_bios = BIO_EMPTY_LIST;
	struct bio_list normal_bios = BIO_EMPTY_LIST;

	if (bio_list_empty(bios))
		return;

	while ((bio = bio_list_pop(bios))) {
		if (bio_triggers_commit(clone, bio))
			bio_list_add(&flush_bios, bio);
		else
			bio_list_add(&normal_bios, bio);
	}

	spin_lock_irqsave(&clone->lock, flags);
	bio_list_merge(&clone->deferred_bios, &normal_bios);
	bio_list_merge(&clone->deferred_flush_bios, &flush_bios);
	spin_unlock_irqrestore(&clone->lock, flags);

	wake_worker(clone);
}