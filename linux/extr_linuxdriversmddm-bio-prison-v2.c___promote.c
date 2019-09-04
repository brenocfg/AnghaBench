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
struct dm_bio_prison_v2 {int dummy; } ;
struct dm_bio_prison_cell_v2 {unsigned int exclusive_level; scalar_t__ shared_count; int /*<<< orphan*/  exclusive_lock; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int __promote(struct dm_bio_prison_v2 *prison,
		     struct dm_bio_prison_cell_v2 *cell,
		     unsigned new_lock_level)
{
	if (!cell->exclusive_lock)
		return -EINVAL;

	cell->exclusive_level = new_lock_level;
	return cell->shared_count > 0;
}