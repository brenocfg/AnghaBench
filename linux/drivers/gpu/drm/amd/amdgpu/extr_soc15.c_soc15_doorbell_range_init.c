#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_ring {int /*<<< orphan*/  doorbell_index; int /*<<< orphan*/  use_doorbell; } ;
struct TYPE_10__ {int /*<<< orphan*/  doorbell_index; int /*<<< orphan*/  use_doorbell; } ;
struct TYPE_11__ {TYPE_4__ ih; } ;
struct TYPE_8__ {int /*<<< orphan*/  sdma_doorbell_range; } ;
struct TYPE_12__ {int num_instances; TYPE_1__* instance; } ;
struct amdgpu_device {TYPE_5__ irq; TYPE_3__* nbio_funcs; TYPE_2__ doorbell_index; TYPE_6__ sdma; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* ih_doorbell_range ) (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* sdma_doorbell_range ) (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {struct amdgpu_ring ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void soc15_doorbell_range_init(struct amdgpu_device *adev)
{
	int i;
	struct amdgpu_ring *ring;

	/* sdma/ih doorbell range are programed by hypervisor */
	if (!amdgpu_sriov_vf(adev)) {
		for (i = 0; i < adev->sdma.num_instances; i++) {
			ring = &adev->sdma.instance[i].ring;
			adev->nbio_funcs->sdma_doorbell_range(adev, i,
				ring->use_doorbell, ring->doorbell_index,
				adev->doorbell_index.sdma_doorbell_range);
		}

		adev->nbio_funcs->ih_doorbell_range(adev, adev->irq.ih.use_doorbell,
						adev->irq.ih.doorbell_index);
	}
}