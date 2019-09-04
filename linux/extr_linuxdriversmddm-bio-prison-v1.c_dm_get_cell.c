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
struct dm_cell_key {int dummy; } ;
struct dm_bio_prison_cell {int dummy; } ;
struct dm_bio_prison {int dummy; } ;

/* Variables and functions */
 int bio_detain (struct dm_bio_prison*,struct dm_cell_key*,int /*<<< orphan*/ *,struct dm_bio_prison_cell*,struct dm_bio_prison_cell**) ; 

int dm_get_cell(struct dm_bio_prison *prison,
		struct dm_cell_key *key,
		struct dm_bio_prison_cell *cell_prealloc,
		struct dm_bio_prison_cell **cell_result)
{
	return bio_detain(prison, key, NULL, cell_prealloc, cell_result);
}