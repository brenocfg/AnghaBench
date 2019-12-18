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
struct dm_bio_prison_v2 {int /*<<< orphan*/  lock; } ;
struct dm_bio_prison_cell_v2 {int dummy; } ;

/* Variables and functions */
 int __promote (struct dm_bio_prison_v2*,struct dm_bio_prison_cell_v2*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int dm_cell_lock_promote_v2(struct dm_bio_prison_v2 *prison,
			    struct dm_bio_prison_cell_v2 *cell,
			    unsigned new_lock_level)
{
	int r;
	unsigned long flags;

	spin_lock_irqsave(&prison->lock, flags);
	r = __promote(prison, cell, new_lock_level);
	spin_unlock_irqrestore(&prison->lock, flags);

	return r;
}