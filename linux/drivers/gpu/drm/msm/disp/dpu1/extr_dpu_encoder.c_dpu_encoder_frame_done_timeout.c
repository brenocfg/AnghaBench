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
typedef  int /*<<< orphan*/  u32 ;
struct timer_list {int dummy; } ;
struct msm_drm_private {int dummy; } ;
struct drm_encoder {TYPE_1__* dev; } ;
struct dpu_encoder_virt {int /*<<< orphan*/  crtc_frame_event_cb_data; int /*<<< orphan*/  (* crtc_frame_event_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  frame_done_timeout_ms; int /*<<< orphan*/ * frame_busy_mask; struct drm_encoder base; } ;
struct TYPE_2__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ENCODER_FRAME_EVENT_ERROR ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DPU_ERROR_ENC (struct dpu_encoder_virt*,char*) ; 
 int /*<<< orphan*/  DRMID (struct drm_encoder*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dpu_encoder_virt* dpu_enc ; 
 int /*<<< orphan*/  frame_done_timer ; 
 struct dpu_encoder_virt* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dpu_enc_frame_done_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpu_encoder_frame_done_timeout(struct timer_list *t)
{
	struct dpu_encoder_virt *dpu_enc = from_timer(dpu_enc, t,
			frame_done_timer);
	struct drm_encoder *drm_enc = &dpu_enc->base;
	struct msm_drm_private *priv;
	u32 event;

	if (!drm_enc->dev || !drm_enc->dev->dev_private) {
		DPU_ERROR("invalid parameters\n");
		return;
	}
	priv = drm_enc->dev->dev_private;

	if (!dpu_enc->frame_busy_mask[0] || !dpu_enc->crtc_frame_event_cb) {
		DRM_DEBUG_KMS("id:%u invalid timeout frame_busy_mask=%lu\n",
			      DRMID(drm_enc), dpu_enc->frame_busy_mask[0]);
		return;
	} else if (!atomic_xchg(&dpu_enc->frame_done_timeout_ms, 0)) {
		DRM_DEBUG_KMS("id:%u invalid timeout\n", DRMID(drm_enc));
		return;
	}

	DPU_ERROR_ENC(dpu_enc, "frame done timeout\n");

	event = DPU_ENCODER_FRAME_EVENT_ERROR;
	trace_dpu_enc_frame_done_timeout(DRMID(drm_enc), event);
	dpu_enc->crtc_frame_event_cb(dpu_enc->crtc_frame_event_cb_data, event);
}