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
struct ttm_placement {int dummy; } ;
struct ttm_buffer_object {int dummy; } ;

/* Variables and functions */
 struct ttm_placement vmw_sys_placement ; 

__attribute__((used)) static void vmw_evict_flags(struct ttm_buffer_object *bo,
		     struct ttm_placement *placement)
{
	*placement = vmw_sys_placement;
}