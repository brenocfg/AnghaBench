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

/* Variables and functions */
 int __promote_or_release (struct dm_bio_prison*,struct dm_bio_prison_cell*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int dm_cell_promote_or_release(struct dm_bio_prison *prison,
			       struct dm_bio_prison_cell *cell)
{
	int r;
	unsigned long flags;

	spin_lock_irqsave(&prison->lock, flags);
	r = __promote_or_release(prison, cell);
	spin_unlock_irqrestore(&prison->lock, flags);

	return r;
}