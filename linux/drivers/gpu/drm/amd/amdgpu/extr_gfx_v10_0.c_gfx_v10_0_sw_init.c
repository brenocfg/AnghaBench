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
struct v10_compute_mqd {int dummy; } ;
struct amdgpu_kiq {int /*<<< orphan*/  irq; int /*<<< orphan*/  ring; } ;
struct TYPE_6__ {int num_mec; int num_pipe_per_mec; int num_queue_per_pipe; } ;
struct TYPE_5__ {int num_me; int num_pipe_per_me; int num_queue_per_pipe; } ;
struct TYPE_8__ {int /*<<< orphan*/  ce_ram_size; struct amdgpu_kiq kiq; TYPE_2__ mec; TYPE_1__ me; int /*<<< orphan*/  gfx_current_status; int /*<<< orphan*/  priv_inst_irq; int /*<<< orphan*/  priv_reg_irq; int /*<<< orphan*/  eop_irq; } ;
struct TYPE_7__ {scalar_t__ load_type; } ;
struct amdgpu_device {int asic_type; TYPE_4__ gfx; TYPE_3__ firmware; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_RLC_BACKDOOR_AUTO ; 
 int /*<<< orphan*/  AMDGPU_GFX_NORMAL_MODE ; 
#define  CHIP_NAVI10 130 
#define  CHIP_NAVI12 129 
#define  CHIP_NAVI14 128 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  F32_CE_PROGRAM_RAM_SIZE ; 
 int /*<<< orphan*/  GFX10_MEC_HPD_SIZE ; 
 int /*<<< orphan*/  GFX_10_1__SRCID__CP_EOP_INTERRUPT ; 
 int /*<<< orphan*/  GFX_10_1__SRCID__CP_IB2_INTERRUPT_PKT ; 
 int /*<<< orphan*/  GFX_10_1__SRCID__CP_PRIV_INSTR_FAULT ; 
 int /*<<< orphan*/  GFX_10_1__SRCID__CP_PRIV_REG_FAULT ; 
 int /*<<< orphan*/  SOC15_IH_CLIENTID_GRBM_CP ; 
 int /*<<< orphan*/  amdgpu_gfx_is_me_queue_enabled (struct amdgpu_device*,int,int,int) ; 
 int /*<<< orphan*/  amdgpu_gfx_is_mec_queue_enabled (struct amdgpu_device*,int,int,int) ; 
 int amdgpu_gfx_kiq_init (struct amdgpu_device*,int /*<<< orphan*/ ) ; 
 int amdgpu_gfx_kiq_init_ring (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int amdgpu_gfx_mqd_sw_init (struct amdgpu_device*,int) ; 
 int amdgpu_irq_add_id (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gfx_v10_0_compute_ring_init (struct amdgpu_device*,int,int,int,int) ; 
 int gfx_v10_0_gfx_ring_init (struct amdgpu_device*,int,int,int,int) ; 
 int /*<<< orphan*/  gfx_v10_0_gpu_early_init (struct amdgpu_device*) ; 
 int gfx_v10_0_me_init (struct amdgpu_device*) ; 
 int gfx_v10_0_mec_init (struct amdgpu_device*) ; 
 int gfx_v10_0_rlc_backdoor_autoload_buffer_init (struct amdgpu_device*) ; 
 int gfx_v10_0_rlc_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v10_0_scratch_init (struct amdgpu_device*) ; 

__attribute__((used)) static int gfx_v10_0_sw_init(void *handle)
{
	int i, j, k, r, ring_id = 0;
	struct amdgpu_kiq *kiq;
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	switch (adev->asic_type) {
	case CHIP_NAVI10:
	case CHIP_NAVI14:
	case CHIP_NAVI12:
		adev->gfx.me.num_me = 1;
		adev->gfx.me.num_pipe_per_me = 2;
		adev->gfx.me.num_queue_per_pipe = 1;
		adev->gfx.mec.num_mec = 2;
		adev->gfx.mec.num_pipe_per_mec = 4;
		adev->gfx.mec.num_queue_per_pipe = 8;
		break;
	default:
		adev->gfx.me.num_me = 1;
		adev->gfx.me.num_pipe_per_me = 1;
		adev->gfx.me.num_queue_per_pipe = 1;
		adev->gfx.mec.num_mec = 1;
		adev->gfx.mec.num_pipe_per_mec = 4;
		adev->gfx.mec.num_queue_per_pipe = 8;
		break;
	}

	/* KIQ event */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_GRBM_CP,
			      GFX_10_1__SRCID__CP_IB2_INTERRUPT_PKT,
			      &adev->gfx.kiq.irq);
	if (r)
		return r;

	/* EOP Event */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_GRBM_CP,
			      GFX_10_1__SRCID__CP_EOP_INTERRUPT,
			      &adev->gfx.eop_irq);
	if (r)
		return r;

	/* Privileged reg */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_GRBM_CP, GFX_10_1__SRCID__CP_PRIV_REG_FAULT,
			      &adev->gfx.priv_reg_irq);
	if (r)
		return r;

	/* Privileged inst */
	r = amdgpu_irq_add_id(adev, SOC15_IH_CLIENTID_GRBM_CP, GFX_10_1__SRCID__CP_PRIV_INSTR_FAULT,
			      &adev->gfx.priv_inst_irq);
	if (r)
		return r;

	adev->gfx.gfx_current_status = AMDGPU_GFX_NORMAL_MODE;

	gfx_v10_0_scratch_init(adev);

	r = gfx_v10_0_me_init(adev);
	if (r)
		return r;

	r = gfx_v10_0_rlc_init(adev);
	if (r) {
		DRM_ERROR("Failed to init rlc BOs!\n");
		return r;
	}

	r = gfx_v10_0_mec_init(adev);
	if (r) {
		DRM_ERROR("Failed to init MEC BOs!\n");
		return r;
	}

	/* set up the gfx ring */
	for (i = 0; i < adev->gfx.me.num_me; i++) {
		for (j = 0; j < adev->gfx.me.num_queue_per_pipe; j++) {
			for (k = 0; k < adev->gfx.me.num_pipe_per_me; k++) {
				if (!amdgpu_gfx_is_me_queue_enabled(adev, i, k, j))
					continue;

				r = gfx_v10_0_gfx_ring_init(adev, ring_id,
							    i, k, j);
				if (r)
					return r;
				ring_id++;
			}
		}
	}

	ring_id = 0;
	/* set up the compute queues - allocate horizontally across pipes */
	for (i = 0; i < adev->gfx.mec.num_mec; ++i) {
		for (j = 0; j < adev->gfx.mec.num_queue_per_pipe; j++) {
			for (k = 0; k < adev->gfx.mec.num_pipe_per_mec; k++) {
				if (!amdgpu_gfx_is_mec_queue_enabled(adev, i, k,
								     j))
					continue;

				r = gfx_v10_0_compute_ring_init(adev, ring_id,
								i, k, j);
				if (r)
					return r;

				ring_id++;
			}
		}
	}

	r = amdgpu_gfx_kiq_init(adev, GFX10_MEC_HPD_SIZE);
	if (r) {
		DRM_ERROR("Failed to init KIQ BOs!\n");
		return r;
	}

	kiq = &adev->gfx.kiq;
	r = amdgpu_gfx_kiq_init_ring(adev, &kiq->ring, &kiq->irq);
	if (r)
		return r;

	r = amdgpu_gfx_mqd_sw_init(adev, sizeof(struct v10_compute_mqd));
	if (r)
		return r;

	/* allocate visible FB for rlc auto-loading fw */
	if (adev->firmware.load_type == AMDGPU_FW_LOAD_RLC_BACKDOOR_AUTO) {
		r = gfx_v10_0_rlc_backdoor_autoload_buffer_init(adev);
		if (r)
			return r;
	}

	adev->gfx.ce_ram_size = F32_CE_PROGRAM_RAM_SIZE;

	gfx_v10_0_gpu_early_init(adev);

	return 0;
}