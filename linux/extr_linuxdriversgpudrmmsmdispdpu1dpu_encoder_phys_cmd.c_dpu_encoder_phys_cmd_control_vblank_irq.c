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
struct dpu_encoder_phys {TYPE_1__* hw_pp; int /*<<< orphan*/  parent; int /*<<< orphan*/  vblank_refcount; } ;
struct TYPE_2__ {scalar_t__ idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DRMID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,scalar_t__,int,char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  INTR_IDX_RDPTR ; 
 scalar_t__ PINGPONG_0 ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int dpu_encoder_helper_register_irq (struct dpu_encoder_phys*,int /*<<< orphan*/ ) ; 
 int dpu_encoder_helper_unregister_irq (struct dpu_encoder_phys*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpu_encoder_phys_cmd_is_master (struct dpu_encoder_phys*) ; 

__attribute__((used)) static int dpu_encoder_phys_cmd_control_vblank_irq(
		struct dpu_encoder_phys *phys_enc,
		bool enable)
{
	int ret = 0;
	int refcount;

	if (!phys_enc || !phys_enc->hw_pp) {
		DPU_ERROR("invalid encoder\n");
		return -EINVAL;
	}

	refcount = atomic_read(&phys_enc->vblank_refcount);

	/* Slave encoders don't report vblank */
	if (!dpu_encoder_phys_cmd_is_master(phys_enc))
		goto end;

	/* protect against negative */
	if (!enable && refcount == 0) {
		ret = -EINVAL;
		goto end;
	}

	DRM_DEBUG_KMS("id:%u pp:%d enable=%s/%d\n", DRMID(phys_enc->parent),
		      phys_enc->hw_pp->idx - PINGPONG_0,
		      enable ? "true" : "false", refcount);

	if (enable && atomic_inc_return(&phys_enc->vblank_refcount) == 1)
		ret = dpu_encoder_helper_register_irq(phys_enc, INTR_IDX_RDPTR);
	else if (!enable && atomic_dec_return(&phys_enc->vblank_refcount) == 0)
		ret = dpu_encoder_helper_unregister_irq(phys_enc,
				INTR_IDX_RDPTR);

end:
	if (ret) {
		DRM_ERROR("vblank irq err id:%u pp:%d ret:%d, enable %s/%d\n",
			  DRMID(phys_enc->parent),
			  phys_enc->hw_pp->idx - PINGPONG_0, ret,
			  enable ? "true" : "false", refcount);
	}

	return ret;
}