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
struct mapped_device {int /*<<< orphan*/  work; int /*<<< orphan*/  wq; int /*<<< orphan*/  deferred_lock; int /*<<< orphan*/  deferred; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void queue_io(struct mapped_device *md, struct bio *bio)
{
	unsigned long flags;

	spin_lock_irqsave(&md->deferred_lock, flags);
	bio_list_add(&md->deferred, bio);
	spin_unlock_irqrestore(&md->deferred_lock, flags);
	queue_work(md->wq, &md->work);
}