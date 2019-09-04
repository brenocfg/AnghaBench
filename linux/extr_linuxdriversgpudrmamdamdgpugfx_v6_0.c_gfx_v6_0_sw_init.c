#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct amdgpu_ring {int use_doorbell; int me; int pipe; int queue; int /*<<< orphan*/  name; scalar_t__ doorbell_index; int /*<<< orphan*/ * ring_obj; } ;
struct TYPE_2__ {int num_gfx_rings; int num_compute_rings; int /*<<< orphan*/  eop_irq; struct amdgpu_ring* compute_ring; struct amdgpu_ring* gfx_ring; int /*<<< orphan*/  priv_inst_irq; int /*<<< orphan*/  priv_reg_irq; } ;
struct amdgpu_device {TYPE_1__ gfx; } ;

/* Variables and functions */
 unsigned int AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE0_EOP ; 
 unsigned int AMDGPU_CP_IRQ_GFX_EOP ; 
 int /*<<< orphan*/  AMDGPU_IH_CLIENTID_LEGACY ; 
 int AMDGPU_MAX_COMPUTE_RINGS ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int amdgpu_ring_init (struct amdgpu_device*,struct amdgpu_ring*,int,int /*<<< orphan*/ *,unsigned int) ; 
 int gfx_v6_0_init_microcode (struct amdgpu_device*) ; 
 int gfx_v6_0_rlc_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v6_0_scratch_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int gfx_v6_0_sw_init(void *handle)
{
	struct amdgpu_ring *ring;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	int i, r;

	r = amdgpu_irq_add_id(adev, AMDGPU_IH_CLIENTID_LEGACY, 181, &adev->gfx.eop_irq);
	if (r)
		return r;

	r = amdgpu_irq_add_id(adev, AMDGPU_IH_CLIENTID_LEGACY, 184, &adev->gfx.priv_reg_irq);
	if (r)
		return r;

	r = amdgpu_irq_add_id(adev, AMDGPU_IH_CLIENTID_LEGACY, 185, &adev->gfx.priv_inst_irq);
	if (r)
		return r;

	gfx_v6_0_scratch_init(adev);

	r = gfx_v6_0_init_microcode(adev);
	if (r) {
		DRM_ERROR("Failed to load gfx firmware!\n");
		return r;
	}

	r = gfx_v6_0_rlc_init(adev);
	if (r) {
		DRM_ERROR("Failed to init rlc BOs!\n");
		return r;
	}

	for (i = 0; i < adev->gfx.num_gfx_rings; i++) {
		ring = &adev->gfx.gfx_ring[i];
		ring->ring_obj = NULL;
		sprintf(ring->name, "gfx");
		r = amdgpu_ring_init(adev, ring, 1024,
				     &adev->gfx.eop_irq, AMDGPU_CP_IRQ_GFX_EOP);
		if (r)
			return r;
	}

	for (i = 0; i < adev->gfx.num_compute_rings; i++) {
		unsigned irq_type;

		if ((i >= 32) || (i >= AMDGPU_MAX_COMPUTE_RINGS)) {
			DRM_ERROR("Too many (%d) compute rings!\n", i);
			break;
		}
		ring = &adev->gfx.compute_ring[i];
		ring->ring_obj = NULL;
		ring->use_doorbell = false;
		ring->doorbell_index = 0;
		ring->me = 1;
		ring->pipe = i;
		ring->queue = i;
		sprintf(ring->name, "comp_%d.%d.%d", ring->me, ring->pipe, ring->queue);
		irq_type = AMDGPU_CP_IRQ_COMPUTE_MEC1_PIPE0_EOP + ring->pipe;
		r = amdgpu_ring_init(adev, ring, 1024,
				     &adev->gfx.eop_irq, irq_type);
		if (r)
			return r;
	}

	return r;
}