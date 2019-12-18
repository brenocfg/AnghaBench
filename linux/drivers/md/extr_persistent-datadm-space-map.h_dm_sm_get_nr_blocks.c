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
struct dm_space_map {int (* get_nr_blocks ) (struct dm_space_map*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int stub1 (struct dm_space_map*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int dm_sm_get_nr_blocks(struct dm_space_map *sm, dm_block_t *count)
{
	return sm->get_nr_blocks(sm, count);
}