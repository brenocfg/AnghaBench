#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_3__ {void* num_busy_placement; void* num_placement; TYPE_2__* busy_placement; TYPE_2__* placement; } ;
struct TYPE_4__ {int flags; scalar_t__ lpfn; scalar_t__ fpfn; } ;
struct virtio_gpu_object {TYPE_1__ placement; TYPE_2__ placement_code; } ;

/* Variables and functions */
 int TTM_PL_FLAG_NO_EVICT ; 
 int TTM_PL_FLAG_TT ; 
 int TTM_PL_MASK_CACHING ; 

__attribute__((used)) static void virtio_gpu_init_ttm_placement(struct virtio_gpu_object *vgbo)
{
	u32 c = 1;

	vgbo->placement.placement = &vgbo->placement_code;
	vgbo->placement.busy_placement = &vgbo->placement_code;
	vgbo->placement_code.fpfn = 0;
	vgbo->placement_code.lpfn = 0;
	vgbo->placement_code.flags =
		TTM_PL_MASK_CACHING | TTM_PL_FLAG_TT |
		TTM_PL_FLAG_NO_EVICT;
	vgbo->placement.num_placement = c;
	vgbo->placement.num_busy_placement = c;

}