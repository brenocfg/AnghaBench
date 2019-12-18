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
struct dm_bio_prison_cell {int /*<<< orphan*/  bios; scalar_t__ holder; int /*<<< orphan*/  node; } ;
struct dm_bio_prison {int /*<<< orphan*/  cells; } ;
struct bio_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_list_add (struct bio_list*,scalar_t__) ; 
 int /*<<< orphan*/  bio_list_merge (struct bio_list*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __cell_release(struct dm_bio_prison *prison,
			   struct dm_bio_prison_cell *cell,
			   struct bio_list *inmates)
{
	rb_erase(&cell->node, &prison->cells);

	if (inmates) {
		if (cell->holder)
			bio_list_add(inmates, cell->holder);
		bio_list_merge(inmates, &cell->bios);
	}
}