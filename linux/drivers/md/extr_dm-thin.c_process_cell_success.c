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
struct thin_c {int /*<<< orphan*/  pool; } ;
struct dm_bio_prison_cell {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cell_success (int /*<<< orphan*/ ,struct dm_bio_prison_cell*) ; 

__attribute__((used)) static void process_cell_success(struct thin_c *tc, struct dm_bio_prison_cell *cell)
{
	cell_success(tc->pool, cell);
}