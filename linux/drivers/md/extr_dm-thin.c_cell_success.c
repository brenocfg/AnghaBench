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
struct pool {int dummy; } ;
struct dm_bio_prison_cell {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cell_error_with_code (struct pool*,struct dm_bio_prison_cell*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cell_success(struct pool *pool, struct dm_bio_prison_cell *cell)
{
	cell_error_with_code(pool, cell, 0);
}