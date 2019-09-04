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
struct amdgpu_ring {int /*<<< orphan*/  name; int /*<<< orphan*/ * ring_obj; } ;
struct TYPE_7__ {int num_mec; int num_pipe_per_mec; int num_queue_per_pipe; } ;
struct TYPE_12__ {int num_gfx_rings; int ce_ram_size; TYPE_1__ mec; int /*<<< orphan*/  eop_irq; struct amdgpu_ring* gfx_ring; int /*<<< orphan*/  priv_inst_irq; int /*<<< orphan*/  priv_reg_irq; } ;
struct TYPE_10__ {int /*<<< orphan*/  gfx_partition_size; } ;
struct TYPE_9__ {int /*<<< orphan*/  gfx_partition_size; } ;
struct TYPE_8__ {int /*<<< orphan*/  gfx_partition_size; } ;
struct TYPE_11__ {int /*<<< orphan*/  oa_gfx_bo; TYPE_4__ oa; int /*<<< orphan*/  gws_gfx_bo; TYPE_3__ gws; int /*<<< orphan*/  gds_gfx_bo; TYPE_2__ mem; } ;
struct amdgpu_device {int asic_type; TYPE_6__ gfx; TYPE_5__ gds; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_CP_IRQ_GFX_EOP ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GDS ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GWS ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_OA ; 
 int /*<<< orphan*/  AMDGPU_IH_CLIENTID_LEGACY ; 
#define  CHIP_BONAIRE 132 
#define  CHIP_HAWAII 131 
#define  CHIP_KABINI 130 
#define  CHIP_KAVERI 129 
#define  CHIP_MULLINS 128 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_gfx_is_mec_queue_enabled (struct amdgpu_device*,int,int,int) ; 
 int amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int amdgpu_ring_init (struct amdgpu_device*,struct amdgpu_ring*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int gfx_v7_0_compute_ring_init (struct amdgpu_device*,int,int,int,int) ; 
 int /*<<< orphan*/  gfx_v7_0_gpu_early_init (struct amdgpu_device*) ; 
 int gfx_v7_0_init_microcode (struct amdgpu_device*) ; 
 int gfx_v7_0_mec_init (struct amdgpu_device*) ; 
 int gfx_v7_0_rlc_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v7_0_scratch_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int gfx_v7_0_sw_init(void *handle)
{
	struct amdgpu_ring *ring;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;
	int i, j, k, r, ring_id;

	switch (adev->asic_type) {
	case CHIP_KAVERI:
		adev->gfx.mec.num_mec = 2;
		break;
	case CHIP_BONAIRE:
	case CHIP_HAWAII:
	case CHIP_KABINI:
	case CHIP_MULLINS:
	default:
		adev->gfx.mec.num_mec = 1;
		break;
	}
	adev->gfx.mec.num_pipe_per_mec = 4;
	adev->gfx.mec.num_queue_per_pipe = 8;

	/* EOP Event */
	r = amdgpu_irq_add_id(adev, AMDGPU_IH_CLIENTID_LEGACY, 181, &adev->gfx.eop_irq);
	if (r)
		return r;

	/* Privileged reg */
	r = amdgpu_irq_add_id(adev, AMDGPU_IH_CLIENTID_LEGACY, 184,
			      &adev->gfx.priv_reg_irq);
	if (r)
		return r;

	/* Privileged inst */
	r = amdgpu_irq_add_id(adev, AMDGPU_IH_CLIENTID_LEGACY, 185,
			      &adev->gfx.priv_inst_irq);
	if (r)
		return r;

	gfx_v7_0_scratch_init(adev);

	r = gfx_v7_0_init_microcode(adev);
	if (r) {
		DRM_ERROR("Failed to load gfx firmware!\n");
		return r;
	}

	r = gfx_v7_0_rlc_init(adev);
	if (r) {
		DRM_ERROR("Failed to init rlc BOs!\n");
		return r;
	}

	/* allocate mec buffers */
	r = gfx_v7_0_mec_init(adev);
	if (r) {
		DRM_ERROR("Failed to init MEC BOs!\n");
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

	/* set up the compute queues - allocate horizontally across pipes */
	ring_id = 0;
	for (i = 0; i < adev->gfx.mec.num_mec; ++i) {
		for (j = 0; j < adev->gfx.mec.num_queue_per_pipe; j++) {
			for (k = 0; k < adev->gfx.mec.num_pipe_per_mec; k++) {
				if (!amdgpu_gfx_is_mec_queue_enabled(adev, i, k, j))
					continue;

				r = gfx_v7_0_compute_ring_init(adev,
								ring_id,
								i, k, j);
				if (r)
					return r;

				ring_id++;
			}
		}
	}

	/* reserve GDS, GWS and OA resource for gfx */
	r = amdgpu_bo_create_kernel(adev, adev->gds.mem.gfx_partition_size,
				    PAGE_SIZE, AMDGPU_GEM_DOMAIN_GDS,
				    &adev->gds.gds_gfx_bo, NULL, NULL);
	if (r)
		return r;

	r = amdgpu_bo_create_kernel(adev, adev->gds.gws.gfx_partition_size,
				    PAGE_SIZE, AMDGPU_GEM_DOMAIN_GWS,
				    &adev->gds.gws_gfx_bo, NULL, NULL);
	if (r)
		return r;

	r = amdgpu_bo_create_kernel(adev, adev->gds.oa.gfx_partition_size,
				    PAGE_SIZE, AMDGPU_GEM_DOMAIN_OA,
				    &adev->gds.oa_gfx_bo, NULL, NULL);
	if (r)
		return r;

	adev->gfx.ce_ram_size = 0x8000;

	gfx_v7_0_gpu_early_init(adev);

	return r;
}