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
struct bio_list {int dummy; } ;

/* Variables and functions */
 int __unlock (struct dm_bio_prison_v2*,struct dm_bio_prison_cell_v2*,struct bio_list*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool dm_cell_unlock_v2(struct dm_bio_prison_v2 *prison,
		       struct dm_bio_prison_cell_v2 *cell,
		       struct bio_list *bios)
{
	bool r;
	unsigned long flags;

	spin_lock_irqsave(&prison->lock, flags);
	r = __unlock(prison, cell, bios);
	spin_unlock_irqrestore(&prison->lock, flags);

	return r;
}