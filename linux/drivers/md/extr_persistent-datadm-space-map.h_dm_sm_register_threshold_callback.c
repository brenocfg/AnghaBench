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
struct dm_space_map {int (* register_threshold_callback ) (struct dm_space_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;} ;
typedef  int /*<<< orphan*/  dm_sm_threshold_fn ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct dm_space_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline int dm_sm_register_threshold_callback(struct dm_space_map *sm,
						    dm_block_t threshold,
						    dm_sm_threshold_fn fn,
						    void *context)
{
	if (sm->register_threshold_callback)
		return sm->register_threshold_callback(sm, threshold, fn, context);

	return -EINVAL;
}