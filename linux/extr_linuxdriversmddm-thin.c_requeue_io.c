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
struct thin_c {int /*<<< orphan*/  lock; int /*<<< orphan*/  retry_on_resume_list; int /*<<< orphan*/  deferred_bio_list; } ;
struct bio_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_DM_REQUEUE ; 
 int /*<<< orphan*/  __merge_bio_list (struct bio_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 int /*<<< orphan*/  error_bio_list (struct bio_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  requeue_deferred_cells (struct thin_c*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void requeue_io(struct thin_c *tc)
{
	struct bio_list bios;
	unsigned long flags;

	bio_list_init(&bios);

	spin_lock_irqsave(&tc->lock, flags);
	__merge_bio_list(&bios, &tc->deferred_bio_list);
	__merge_bio_list(&bios, &tc->retry_on_resume_list);
	spin_unlock_irqrestore(&tc->lock, flags);

	error_bio_list(&bios, BLK_STS_DM_REQUEUE);
	requeue_deferred_cells(tc);
}