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
struct thin_c {int /*<<< orphan*/  lock; int /*<<< orphan*/  retry_on_resume_list; } ;
struct dm_thin_endio_hook {struct thin_c* tc; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 struct dm_thin_endio_hook* dm_per_bio_data (struct bio*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void retry_on_resume(struct bio *bio)
{
	struct dm_thin_endio_hook *h = dm_per_bio_data(bio, sizeof(struct dm_thin_endio_hook));
	struct thin_c *tc = h->tc;
	unsigned long flags;

	spin_lock_irqsave(&tc->lock, flags);
	bio_list_add(&tc->retry_on_resume_list, bio);
	spin_unlock_irqrestore(&tc->lock, flags);
}