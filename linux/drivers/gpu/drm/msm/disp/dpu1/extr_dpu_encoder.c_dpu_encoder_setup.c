#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct msm_drm_private {int /*<<< orphan*/  kms; } ;
struct msm_display_info {scalar_t__ intf_type; } ;
struct drm_encoder {int dummy; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct dpu_kms {int dummy; } ;
struct dpu_encoder_virt {int /*<<< orphan*/  disp_info; int /*<<< orphan*/  vsync_event_work; int /*<<< orphan*/  idle_timeout; int /*<<< orphan*/  delayed_off_work; int /*<<< orphan*/  rc_lock; int /*<<< orphan*/  vsync_event_timer; int /*<<< orphan*/  frame_done_timer; int /*<<< orphan*/  frame_done_timeout_ms; int /*<<< orphan*/  enc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_ENC (struct dpu_encoder_virt*,char*) ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 scalar_t__ DRM_MODE_ENCODER_DSI ; 
 int /*<<< orphan*/  IDLE_TIMEOUT ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpu_encoder_destroy (struct drm_encoder*) ; 
 int /*<<< orphan*/  dpu_encoder_frame_done_timeout ; 
 int /*<<< orphan*/  dpu_encoder_off_work ; 
 int dpu_encoder_setup_display (struct dpu_encoder_virt*,struct dpu_kms*,struct msm_display_info*) ; 
 int /*<<< orphan*/  dpu_encoder_vsync_event_handler ; 
 int /*<<< orphan*/  dpu_encoder_vsync_event_work_handler ; 
 int /*<<< orphan*/  kthread_init_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct msm_display_info*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dpu_encoder_virt* to_dpu_encoder_virt (struct drm_encoder*) ; 
 struct dpu_kms* to_dpu_kms (int /*<<< orphan*/ ) ; 

int dpu_encoder_setup(struct drm_device *dev, struct drm_encoder *enc,
		struct msm_display_info *disp_info)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct dpu_kms *dpu_kms = to_dpu_kms(priv->kms);
	struct drm_encoder *drm_enc = NULL;
	struct dpu_encoder_virt *dpu_enc = NULL;
	int ret = 0;

	dpu_enc = to_dpu_encoder_virt(enc);

	mutex_init(&dpu_enc->enc_lock);
	ret = dpu_encoder_setup_display(dpu_enc, dpu_kms, disp_info);
	if (ret)
		goto fail;

	atomic_set(&dpu_enc->frame_done_timeout_ms, 0);
	timer_setup(&dpu_enc->frame_done_timer,
			dpu_encoder_frame_done_timeout, 0);

	if (disp_info->intf_type == DRM_MODE_ENCODER_DSI)
		timer_setup(&dpu_enc->vsync_event_timer,
				dpu_encoder_vsync_event_handler,
				0);


	mutex_init(&dpu_enc->rc_lock);
	INIT_DELAYED_WORK(&dpu_enc->delayed_off_work,
			dpu_encoder_off_work);
	dpu_enc->idle_timeout = IDLE_TIMEOUT;

	kthread_init_work(&dpu_enc->vsync_event_work,
			dpu_encoder_vsync_event_work_handler);

	memcpy(&dpu_enc->disp_info, disp_info, sizeof(*disp_info));

	DPU_DEBUG_ENC(dpu_enc, "created\n");

	return ret;

fail:
	DPU_ERROR("failed to create encoder\n");
	if (drm_enc)
		dpu_encoder_destroy(drm_enc);

	return ret;


}