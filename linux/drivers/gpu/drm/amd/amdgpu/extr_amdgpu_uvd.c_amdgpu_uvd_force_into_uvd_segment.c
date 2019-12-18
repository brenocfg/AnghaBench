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
struct TYPE_3__ {int num_placement; } ;
struct amdgpu_bo {TYPE_2__* placements; TYPE_1__ placement; } ;
struct TYPE_4__ {int fpfn; int lpfn; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 

__attribute__((used)) static void amdgpu_uvd_force_into_uvd_segment(struct amdgpu_bo *abo)
{
	int i;
	for (i = 0; i < abo->placement.num_placement; ++i) {
		abo->placements[i].fpfn = 0 >> PAGE_SHIFT;
		abo->placements[i].lpfn = (256 * 1024 * 1024) >> PAGE_SHIFT;
	}
}