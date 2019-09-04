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
struct dm_bio_prison_cell {int /*<<< orphan*/  bios; int /*<<< orphan*/  holder; int /*<<< orphan*/  node; } ;
struct dm_bio_prison {int /*<<< orphan*/  cells; } ;

/* Variables and functions */
 scalar_t__ bio_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_list_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __promote_or_release(struct dm_bio_prison *prison,
				struct dm_bio_prison_cell *cell)
{
	if (bio_list_empty(&cell->bios)) {
		rb_erase(&cell->node, &prison->cells);
		return 1;
	}

	cell->holder = bio_list_pop(&cell->bios);
	return 0;
}