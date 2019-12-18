#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int num_instances; TYPE_3__* instance; scalar_t__ has_page_queue; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_4__ sdma; } ;
struct TYPE_6__ {int me; int /*<<< orphan*/ * funcs; } ;
struct TYPE_5__ {int me; int /*<<< orphan*/ * funcs; } ;
struct TYPE_7__ {TYPE_2__ page; TYPE_1__ ring; } ;

/* Variables and functions */
 scalar_t__ CHIP_ARCTURUS ; 
 int /*<<< orphan*/  sdma_v4_0_page_ring_funcs ; 
 int /*<<< orphan*/  sdma_v4_0_page_ring_funcs_2nd_mmhub ; 
 int /*<<< orphan*/  sdma_v4_0_ring_funcs ; 
 int /*<<< orphan*/  sdma_v4_0_ring_funcs_2nd_mmhub ; 

__attribute__((used)) static void sdma_v4_0_set_ring_funcs(struct amdgpu_device *adev)
{
	int i;

	for (i = 0; i < adev->sdma.num_instances; i++) {
		if (adev->asic_type == CHIP_ARCTURUS && i >= 5)
			adev->sdma.instance[i].ring.funcs =
					&sdma_v4_0_ring_funcs_2nd_mmhub;
		else
			adev->sdma.instance[i].ring.funcs =
					&sdma_v4_0_ring_funcs;
		adev->sdma.instance[i].ring.me = i;
		if (adev->sdma.has_page_queue) {
			if (adev->asic_type == CHIP_ARCTURUS && i >= 5)
				adev->sdma.instance[i].page.funcs =
					&sdma_v4_0_page_ring_funcs_2nd_mmhub;
			else
				adev->sdma.instance[i].page.funcs =
					&sdma_v4_0_page_ring_funcs;
			adev->sdma.instance[i].page.me = i;
		}
	}
}