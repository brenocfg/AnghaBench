#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_ring {int use_doorbell; int use_pollmem; int /*<<< orphan*/  name; int /*<<< orphan*/  doorbell_index; int /*<<< orphan*/ * ring_obj; } ;
struct TYPE_6__ {int num_instances; int /*<<< orphan*/  trap_irq; TYPE_1__* instance; int /*<<< orphan*/  illegal_inst_irq; } ;
struct TYPE_5__ {int /*<<< orphan*/ * sdma_engine; } ;
struct amdgpu_device {TYPE_3__ sdma; TYPE_2__ doorbell_index; } ;
struct TYPE_4__ {struct amdgpu_ring ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_IRQ_CLIENTID_LEGACY ; 
 int /*<<< orphan*/  AMDGPU_SDMA_IRQ_INSTANCE0 ; 
 int /*<<< orphan*/  AMDGPU_SDMA_IRQ_INSTANCE1 ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int VISLANDS30_IV_SRCID_SDMA_SRBM_WRITE ; 
 int VISLANDS30_IV_SRCID_SDMA_TRAP ; 
 int amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int amdgpu_ring_init (struct amdgpu_device*,struct amdgpu_ring*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int sdma_v3_0_init_microcode (struct amdgpu_device*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int sdma_v3_0_sw_init(void *handle)
{
	struct amdgpu_ring *ring;
	int r, i;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	/* SDMA trap event */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_SDMA_TRAP,
			      &adev->sdma.trap_irq);
	if (r)
		return r;

	/* SDMA Privileged inst */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 241,
			      &adev->sdma.illegal_inst_irq);
	if (r)
		return r;

	/* SDMA Privileged inst */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_SDMA_SRBM_WRITE,
			      &adev->sdma.illegal_inst_irq);
	if (r)
		return r;

	r = sdma_v3_0_init_microcode(adev);
	if (r) {
		DRM_ERROR("Failed to load sdma firmware!\n");
		return r;
	}

	for (i = 0; i < adev->sdma.num_instances; i++) {
		ring = &adev->sdma.instance[i].ring;
		ring->ring_obj = NULL;
		if (!amdgpu_sriov_vf(adev)) {
			ring->use_doorbell = true;
			ring->doorbell_index = adev->doorbell_index.sdma_engine[i];
		} else {
			ring->use_pollmem = true;
		}

		sprintf(ring->name, "sdma%d", i);
		r = amdgpu_ring_init(adev, ring, 1024,
				     &adev->sdma.trap_irq,
				     (i == 0) ?
				     AMDGPU_SDMA_IRQ_INSTANCE0 :
				     AMDGPU_SDMA_IRQ_INSTANCE1);
		if (r)
			return r;
	}

	return r;
}