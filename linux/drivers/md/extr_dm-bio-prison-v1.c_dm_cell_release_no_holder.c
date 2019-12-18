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
struct dm_bio_prison_cell {int dummy; } ;
struct dm_bio_prison {int /*<<< orphan*/  lock; } ;
struct bio_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cell_release_no_holder (struct dm_bio_prison*,struct dm_bio_prison_cell*,struct bio_list*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void dm_cell_release_no_holder(struct dm_bio_prison *prison,
			       struct dm_bio_prison_cell *cell,
			       struct bio_list *inmates)
{
	unsigned long flags;

	spin_lock_irqsave(&prison->lock, flags);
	__cell_release_no_holder(prison, cell, inmates);
	spin_unlock_irqrestore(&prison->lock, flags);
}