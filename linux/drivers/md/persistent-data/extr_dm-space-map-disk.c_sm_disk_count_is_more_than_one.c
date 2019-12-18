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
typedef  int uint32_t ;
struct dm_space_map {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int sm_disk_get_count (struct dm_space_map*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int sm_disk_count_is_more_than_one(struct dm_space_map *sm, dm_block_t b,
					  int *result)
{
	int r;
	uint32_t count;

	r = sm_disk_get_count(sm, b, &count);
	if (r)
		return r;

	*result = count > 1;

	return 0;
}