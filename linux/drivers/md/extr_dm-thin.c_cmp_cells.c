#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dm_bio_prison_cell {TYPE_2__* holder; } ;
struct TYPE_3__ {scalar_t__ bi_sector; } ;
struct TYPE_4__ {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static int cmp_cells(const void *lhs, const void *rhs)
{
	struct dm_bio_prison_cell *lhs_cell = *((struct dm_bio_prison_cell **) lhs);
	struct dm_bio_prison_cell *rhs_cell = *((struct dm_bio_prison_cell **) rhs);

	BUG_ON(!lhs_cell->holder);
	BUG_ON(!rhs_cell->holder);

	if (lhs_cell->holder->bi_iter.bi_sector < rhs_cell->holder->bi_iter.bi_sector)
		return -1;

	if (lhs_cell->holder->bi_iter.bi_sector > rhs_cell->holder->bi_iter.bi_sector)
		return 1;

	return 0;
}