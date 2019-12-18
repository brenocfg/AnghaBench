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
struct dpu_encoder_phys {TYPE_1__* hw_intf; int /*<<< orphan*/  parent; int /*<<< orphan*/  vblank_refcount; } ;
struct TYPE_2__ {scalar_t__ idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DRMID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,scalar_t__,int,int,int) ; 
 int EINVAL ; 
 scalar_t__ INTF_0 ; 
 int /*<<< orphan*/  INTR_IDX_VSYNC ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int dpu_encoder_helper_register_irq (struct dpu_encoder_phys*,int /*<<< orphan*/ ) ; 
 int dpu_encoder_helper_unregister_irq (struct dpu_encoder_phys*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpu_encoder_phys_vid_is_master (struct dpu_encoder_phys*) ; 

__attribute__((used)) static int dpu_encoder_phys_vid_control_vblank_irq(
		struct dpu_encoder_phys *phys_enc,
		bool enable)
{
	int ret = 0;
	int refcount;

	if (!phys_enc) {
		DPU_ERROR("invalid encoder\n");
		return -EINVAL;
	}

	refcount = atomic_read(&phys_enc->vblank_refcount);

	/* Slave encoders don't report vblank */
	if (!dpu_encoder_phys_vid_is_master(phys_enc))
		goto end;

	/* protect against negative */
	if (!enable && refcount == 0) {
		ret = -EINVAL;
		goto end;
	}

	DRM_DEBUG_KMS("id:%u enable=%d/%d\n", DRMID(phys_enc->parent), enable,
		      atomic_read(&phys_enc->vblank_refcount));

	if (enable && atomic_inc_return(&phys_enc->vblank_refcount) == 1)
		ret = dpu_encoder_helper_register_irq(phys_enc, INTR_IDX_VSYNC);
	else if (!enable && atomic_dec_return(&phys_enc->vblank_refcount) == 0)
		ret = dpu_encoder_helper_unregister_irq(phys_enc,
				INTR_IDX_VSYNC);

end:
	if (ret) {
		DRM_ERROR("failed: id:%u intf:%d ret:%d enable:%d refcnt:%d\n",
			  DRMID(phys_enc->parent),
			  phys_enc->hw_intf->idx - INTF_0, ret, enable,
			  refcount);
	}
	return ret;
}