#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* funcs; } ;
struct TYPE_10__ {int /*<<< orphan*/  queue; int /*<<< orphan*/  pipe; int /*<<< orphan*/  me; } ;
struct TYPE_6__ {TYPE_5__ ring; } ;
struct TYPE_9__ {TYPE_3__ rlc; TYPE_1__ kiq; int /*<<< orphan*/  priv_inst_irq; int /*<<< orphan*/  priv_reg_irq; int /*<<< orphan*/  cp_ecc_error_irq; } ;
struct amdgpu_device {TYPE_4__ gfx; int /*<<< orphan*/  srbm_mutex; int /*<<< orphan*/  in_suspend; int /*<<< orphan*/  in_gpu_reset; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* stop ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CP_PQ_WPTR_POLL_CNTL ; 
 int /*<<< orphan*/  EN ; 
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  WREG32_FIELD15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_irq_put (struct amdgpu_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_cp_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v9_0_cp_gfx_enable (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gfx_v9_0_csb_vram_unpin (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_kcq_disable (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfx_v9_0_kiq_fini_register (TYPE_5__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc15_grbm_select (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 

__attribute__((used)) static int gfx_v9_0_hw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	amdgpu_irq_put(adev, &adev->gfx.cp_ecc_error_irq, 0);
	amdgpu_irq_put(adev, &adev->gfx.priv_reg_irq, 0);
	amdgpu_irq_put(adev, &adev->gfx.priv_inst_irq, 0);

	/* disable KCQ to avoid CPC touch memory not valid anymore */
	gfx_v9_0_kcq_disable(adev);

	if (amdgpu_sriov_vf(adev)) {
		gfx_v9_0_cp_gfx_enable(adev, false);
		/* must disable polling for SRIOV when hw finished, otherwise
		 * CPC engine may still keep fetching WB address which is already
		 * invalid after sw finished and trigger DMAR reading error in
		 * hypervisor side.
		 */
		WREG32_FIELD15(GC, 0, CP_PQ_WPTR_POLL_CNTL, EN, 0);
		return 0;
	}

	/* Use deinitialize sequence from CAIL when unbinding device from driver,
	 * otherwise KIQ is hanging when binding back
	 */
	if (!adev->in_gpu_reset && !adev->in_suspend) {
		mutex_lock(&adev->srbm_mutex);
		soc15_grbm_select(adev, adev->gfx.kiq.ring.me,
				adev->gfx.kiq.ring.pipe,
				adev->gfx.kiq.ring.queue, 0);
		gfx_v9_0_kiq_fini_register(&adev->gfx.kiq.ring);
		soc15_grbm_select(adev, 0, 0, 0, 0);
		mutex_unlock(&adev->srbm_mutex);
	}

	gfx_v9_0_cp_enable(adev, false);
	adev->gfx.rlc.funcs->stop(adev);

	gfx_v9_0_csb_vram_unpin(adev);

	return 0;
}