#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vi_mqd_allocation {int dummy; } ;
struct amdgpu_ring {int use_doorbell; int /*<<< orphan*/  doorbell_index; int /*<<< orphan*/  name; int /*<<< orphan*/ * ring_obj; } ;
struct amdgpu_kiq {int /*<<< orphan*/  irq; int /*<<< orphan*/  ring; } ;
struct TYPE_9__ {int num_mec; int num_pipe_per_mec; int num_queue_per_pipe; } ;
struct TYPE_8__ {int /*<<< orphan*/  work; } ;
struct TYPE_14__ {int num_gfx_rings; int ce_ram_size; struct amdgpu_kiq kiq; TYPE_2__ mec; int /*<<< orphan*/  eop_irq; struct amdgpu_ring* gfx_ring; int /*<<< orphan*/  gfx_current_status; TYPE_1__ sq_work; int /*<<< orphan*/  sq_irq; int /*<<< orphan*/  cp_ecc_error_irq; int /*<<< orphan*/  priv_inst_irq; int /*<<< orphan*/  priv_reg_irq; } ;
struct TYPE_12__ {int /*<<< orphan*/  gfx_partition_size; } ;
struct TYPE_11__ {int /*<<< orphan*/  gfx_partition_size; } ;
struct TYPE_10__ {int /*<<< orphan*/  gfx_partition_size; } ;
struct TYPE_13__ {int /*<<< orphan*/  oa_gfx_bo; TYPE_5__ oa; int /*<<< orphan*/  gws_gfx_bo; TYPE_4__ gws; int /*<<< orphan*/  gds_gfx_bo; TYPE_3__ mem; } ;
struct amdgpu_device {int asic_type; TYPE_7__ gfx; TYPE_6__ gds; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_CP_IRQ_GFX_EOP ; 
 int /*<<< orphan*/  AMDGPU_DOORBELL_GFX_RING0 ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GDS ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GWS ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_OA ; 
 int /*<<< orphan*/  AMDGPU_GFX_NORMAL_MODE ; 
 int /*<<< orphan*/  AMDGPU_IH_CLIENTID_LEGACY ; 
#define  CHIP_CARRIZO 136 
#define  CHIP_FIJI 135 
#define  CHIP_POLARIS10 134 
#define  CHIP_POLARIS11 133 
#define  CHIP_POLARIS12 132 
#define  CHIP_STONEY 131 
#define  CHIP_TONGA 130 
#define  CHIP_TOPAZ 129 
#define  CHIP_VEGAM 128 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  GFX8_MEC_HPD_SIZE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  VISLANDS30_IV_SRCID_CP_ECC_ERROR ; 
 int /*<<< orphan*/  VISLANDS30_IV_SRCID_CP_END_OF_PIPE ; 
 int /*<<< orphan*/  VISLANDS30_IV_SRCID_CP_INT_IB2 ; 
 int /*<<< orphan*/  VISLANDS30_IV_SRCID_CP_PRIV_INSTR_FAULT ; 
 int /*<<< orphan*/  VISLANDS30_IV_SRCID_CP_PRIV_REG_FAULT ; 
 int /*<<< orphan*/  VISLANDS30_IV_SRCID_SQ_INTERRUPT_MSG ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int amdgpu_gfx_compute_mqd_sw_init (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  amdgpu_gfx_is_mec_queue_enabled (struct amdgpu_device*,int,int,int) ; 
 int amdgpu_gfx_kiq_init (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int amdgpu_gfx_kiq_init_ring (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int amdgpu_ring_init (struct amdgpu_device*,struct amdgpu_ring*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int gfx_v8_0_compute_ring_init (struct amdgpu_device*,int,int,int,int) ; 
 int gfx_v8_0_gpu_early_init (struct amdgpu_device*) ; 
 int gfx_v8_0_init_microcode (struct amdgpu_device*) ; 
 int gfx_v8_0_mec_init (struct amdgpu_device*) ; 
 int gfx_v8_0_rlc_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_scratch_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v8_0_sq_irq_work_func ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int gfx_v8_0_sw_init(void *handle)
{
	int i, j, k, r, ring_id;
	struct amdgpu_ring *ring;
	struct amdgpu_kiq *kiq;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	switch (adev->asic_type) {
	case CHIP_TONGA:
	case CHIP_CARRIZO:
	case CHIP_FIJI:
	case CHIP_POLARIS10:
	case CHIP_POLARIS11:
	case CHIP_POLARIS12:
	case CHIP_VEGAM:
		adev->gfx.mec.num_mec = 2;
		break;
	case CHIP_TOPAZ:
	case CHIP_STONEY:
	default:
		adev->gfx.mec.num_mec = 1;
		break;
	}

	adev->gfx.mec.num_pipe_per_mec = 4;
	adev->gfx.mec.num_queue_per_pipe = 8;

	/* KIQ event */
	r = amdgpu_irq_add_id(adev, AMDGPU_IH_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_CP_INT_IB2, &adev->gfx.kiq.irq);
	if (r)
		return r;

	/* EOP Event */
	r = amdgpu_irq_add_id(adev, AMDGPU_IH_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_CP_END_OF_PIPE, &adev->gfx.eop_irq);
	if (r)
		return r;

	/* Privileged reg */
	r = amdgpu_irq_add_id(adev, AMDGPU_IH_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_CP_PRIV_REG_FAULT,
			      &adev->gfx.priv_reg_irq);
	if (r)
		return r;

	/* Privileged inst */
	r = amdgpu_irq_add_id(adev, AMDGPU_IH_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_CP_PRIV_INSTR_FAULT,
			      &adev->gfx.priv_inst_irq);
	if (r)
		return r;

	/* Add CP EDC/ECC irq  */
	r = amdgpu_irq_add_id(adev, AMDGPU_IH_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_CP_ECC_ERROR,
			      &adev->gfx.cp_ecc_error_irq);
	if (r)
		return r;

	/* SQ interrupts. */
	r = amdgpu_irq_add_id(adev, AMDGPU_IH_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_SQ_INTERRUPT_MSG,
			      &adev->gfx.sq_irq);
	if (r) {
		DRM_ERROR("amdgpu_irq_add() for SQ failed: %d\n", r);
		return r;
	}

	INIT_WORK(&adev->gfx.sq_work.work, gfx_v8_0_sq_irq_work_func);

	adev->gfx.gfx_current_status = AMDGPU_GFX_NORMAL_MODE;

	gfx_v8_0_scratch_init(adev);

	r = gfx_v8_0_init_microcode(adev);
	if (r) {
		DRM_ERROR("Failed to load gfx firmware!\n");
		return r;
	}

	r = gfx_v8_0_rlc_init(adev);
	if (r) {
		DRM_ERROR("Failed to init rlc BOs!\n");
		return r;
	}

	r = gfx_v8_0_mec_init(adev);
	if (r) {
		DRM_ERROR("Failed to init MEC BOs!\n");
		return r;
	}

	/* set up the gfx ring */
	for (i = 0; i < adev->gfx.num_gfx_rings; i++) {
		ring = &adev->gfx.gfx_ring[i];
		ring->ring_obj = NULL;
		sprintf(ring->name, "gfx");
		/* no gfx doorbells on iceland */
		if (adev->asic_type != CHIP_TOPAZ) {
			ring->use_doorbell = true;
			ring->doorbell_index = AMDGPU_DOORBELL_GFX_RING0;
		}

		r = amdgpu_ring_init(adev, ring, 1024, &adev->gfx.eop_irq,
				     AMDGPU_CP_IRQ_GFX_EOP);
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

				r = gfx_v8_0_compute_ring_init(adev,
								ring_id,
								i, k, j);
				if (r)
					return r;

				ring_id++;
			}
		}
	}

	r = amdgpu_gfx_kiq_init(adev, GFX8_MEC_HPD_SIZE);
	if (r) {
		DRM_ERROR("Failed to init KIQ BOs!\n");
		return r;
	}

	kiq = &adev->gfx.kiq;
	r = amdgpu_gfx_kiq_init_ring(adev, &kiq->ring, &kiq->irq);
	if (r)
		return r;

	/* create MQD for all compute queues as well as KIQ for SRIOV case */
	r = amdgpu_gfx_compute_mqd_sw_init(adev, sizeof(struct vi_mqd_allocation));
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

	r = gfx_v8_0_gpu_early_init(adev);
	if (r)
		return r;

	return 0;
}