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
struct pool {int /*<<< orphan*/  prison; } ;
struct dm_bio_prison_cell {int dummy; } ;
struct bio_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_bio_prison_free_cell (int /*<<< orphan*/ ,struct dm_bio_prison_cell*) ; 
 int /*<<< orphan*/  dm_cell_release_no_holder (int /*<<< orphan*/ ,struct dm_bio_prison_cell*,struct bio_list*) ; 

__attribute__((used)) static void cell_release_no_holder(struct pool *pool,
				   struct dm_bio_prison_cell *cell,
				   struct bio_list *bios)
{
	dm_cell_release_no_holder(pool->prison, cell, bios);
	dm_bio_prison_free_cell(pool->prison, cell);
}