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
struct amdgpu_ring {int use_doorbell; int /*<<< orphan*/  name; int /*<<< orphan*/ * ring_obj; } ;
struct TYPE_4__ {int num_instances; int /*<<< orphan*/  trap_irq; TYPE_1__* instance; } ;
struct amdgpu_device {TYPE_2__ sdma; } ;
struct TYPE_3__ {struct amdgpu_ring ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_IRQ_CLIENTID_LEGACY ; 
 int /*<<< orphan*/  AMDGPU_SDMA_IRQ_INSTANCE0 ; 
 int /*<<< orphan*/  AMDGPU_SDMA_IRQ_INSTANCE1 ; 
 int amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int amdgpu_ring_init (struct amdgpu_device*,struct amdgpu_ring*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int si_dma_sw_init(void *handle)
{
	struct amdgpu_ring *ring;
	int r, i;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	/* DMA0 trap event */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 224,
			      &adev->sdma.trap_irq);
	if (r)
		return r;

	/* DMA1 trap event */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 244,
			      &adev->sdma.trap_irq);
	if (r)
		return r;

	for (i = 0; i < adev->sdma.num_instances; i++) {
		ring = &adev->sdma.instance[i].ring;
		ring->ring_obj = NULL;
		ring->use_doorbell = false;
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