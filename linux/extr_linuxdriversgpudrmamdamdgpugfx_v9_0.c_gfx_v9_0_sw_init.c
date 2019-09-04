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
struct v9_mqd_allocation {int dummy; } ;
struct amdgpu_ring {int use_doorbell; int doorbell_index; int /*<<< orphan*/  name; int /*<<< orphan*/ * ring_obj; } ;
struct amdgpu_kiq {int /*<<< orphan*/  irq; int /*<<< orphan*/  ring; } ;
struct TYPE_7__ {int num_mec; int num_pipe_per_mec; int num_queue_per_pipe; } ;
struct TYPE_12__ {int num_gfx_rings; int ce_ram_size; struct amdgpu_kiq kiq; TYPE_1__ mec; int /*<<< orphan*/  eop_irq; struct amdgpu_ring* gfx_ring; int /*<<< orphan*/  gfx_current_status; int /*<<< orphan*/  priv_inst_irq; int /*<<< orphan*/  priv_reg_irq; } ;
struct TYPE_10__ {int /*<<< orphan*/  gfx_partition_size; } ;
struct TYPE_9__ {int /*<<< orphan*/  gfx_partition_size; } ;
struct TYPE_8__ {int /*<<< orphan*/  gfx_partition_size; } ;
struct TYPE_11__ {int /*<<< orphan*/  oa_gfx_bo; TYPE_4__ oa; int /*<<< orphan*/  gws_gfx_bo; TYPE_3__ gws; int /*<<< orphan*/  gds_gfx_bo; TYPE_2__ mem; } ;
struct amdgpu_device {int asic_type; TYPE_6__ gfx; TYPE_5__ gds; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_CP_IRQ_GFX_EOP ; 
 int AMDGPU_DOORBELL64_GFX_RING0 ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GDS ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GWS ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_OA ; 
 int /*<<< orphan*/  AMDGPU_GFX_NORMAL_MODE ; 
#define  CHIP_RAVEN 131 
#define  CHIP_VEGA10 130 
#define  CHIP_VEGA12 129 
#define  CHIP_VEGA20 128 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  GFX9_MEC_HPD_SIZE ; 
 int /*<<< orphan*/  GFX_9_0__SRCID__CP_EOP_INTERRUPT ; 
 int /*<<< orphan*/  GFX_9_0__SRCID__CP_IB2_INTERRUPT_PKT ; 
 int /*<<< orphan*/  GFX_9_0__SRCID__CP_PRIV_INSTR_FAULT ; 
 int /*<<< orphan*/  GFX_9_0__SRCID__CP_PRIV_REG_FAULT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  SOC15_IH_CLIENTID_GRBM_CP ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int amdgpu_gfx_compute_mqd_sw_init (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  amdgpu_gfx_is_mec_queue_enabled (struct amdgpu_device*,int,int,int) ; 
 int amdgpu_gfx_kiq_init (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int amdgpu_gfx_kiq_init_ring (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int amdgpu_ring_init (struct amdgpu_device*,struct amdgpu_ring*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int gfx_v9_0_compute_ring_init (struct amdgpu_device*,int,int,int,int) ; 
 int gfx_v9_0_gpu_early_init (struct amdgpu_device*) ; 
 int gfx_v9_0_init_microcode (struct amdgpu_device*) ; 
 int gfx_v9_0_mec_init (struct amdgpu_device*) ; 
 int gfx_v9_0_ngg_init (struct amdgpu_device*) ; 
 int gfx_v9_0_rlc_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_scratch_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int gfx_v9_0_sw_init(void *handle)
{
	int i, j, k, r, ring_id;
	struct amdgpu_ring *ring;
	struct amdgpu_kiq *kiq;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	switch (adev->asic_type) {
	case CHIP_VEGA10:
	case CHIP_VEGA12:
	case CHIP_VEGA20:
	case CHIP_RAVEN:
		adev->gfx.mec.num_mec = 2;
		break;
	default:
		adev->gfx.mec.num_mec = 1;
		break;
	}

	adev->gfx.mec.num_pipe_per_mec = 4;
	adev->gfx.mec.num_queue_per_pipe = 8;

	/* KIQ event */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_GRBM_CP, GFX_9_0__SRCID__CP_IB2_INTERRUPT_PKT, &adev->gfx.kiq.irq);
	if (r)
		return r;

	/* EOP Event */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_GRBM_CP, GFX_9_0__SRCID__CP_EOP_INTERRUPT, &adev->gfx.eop_irq);
	if (r)
		return r;

	/* Privileged reg */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_GRBM_CP, GFX_9_0__SRCID__CP_PRIV_REG_FAULT,
			      &adev->gfx.priv_reg_irq);
	if (r)
		return r;

	/* Privileged inst */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_GRBM_CP, GFX_9_0__SRCID__CP_PRIV_INSTR_FAULT,
			      &adev->gfx.priv_inst_irq);
	if (r)
		return r;

	adev->gfx.gfx_current_status = AMDGPU_GFX_NORMAL_MODE;

	gfx_v9_0_scratch_init(adev);

	r = gfx_v9_0_init_microcode(adev);
	if (r) {
		DRM_ERROR("Failed to load gfx firmware!\n");
		return r;
	}

	r = gfx_v9_0_rlc_init(adev);
	if (r) {
		DRM_ERROR("Failed to init rlc BOs!\n");
		return r;
	}

	r = gfx_v9_0_mec_init(adev);
	if (r) {
		DRM_ERROR("Failed to init MEC BOs!\n");
		return r;
	}

	/* set up the gfx ring */
	for (i = 0; i < adev->gfx.num_gfx_rings; i++) {
		ring = &adev->gfx.gfx_ring[i];
		ring->ring_obj = NULL;
		if (!i)
			sprintf(ring->name, "gfx");
		else
			sprintf(ring->name, "gfx_%d", i);
		ring->use_doorbell = true;
		ring->doorbell_index = AMDGPU_DOORBELL64_GFX_RING0 << 1;
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

				r = gfx_v9_0_compute_ring_init(adev,
							       ring_id,
							       i, k, j);
				if (r)
					return r;

				ring_id++;
			}
		}
	}

	r = amdgpu_gfx_kiq_init(adev, GFX9_MEC_HPD_SIZE);
	if (r) {
		DRM_ERROR("Failed to init KIQ BOs!\n");
		return r;
	}

	kiq = &adev->gfx.kiq;
	r = amdgpu_gfx_kiq_init_ring(adev, &kiq->ring, &kiq->irq);
	if (r)
		return r;

	/* create MQD for all compute queues as wel as KIQ for SRIOV case */
	r = amdgpu_gfx_compute_mqd_sw_init(adev, sizeof(struct v9_mqd_allocation));
	if (r)
		return r;

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

	r = gfx_v9_0_gpu_early_init(adev);
	if (r)
		return r;

	r = gfx_v9_0_ngg_init(adev);
	if (r)
		return r;

	return 0;
}