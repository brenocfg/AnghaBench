#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct msm_drm_thread {int dummy; } ;
struct msm_drm_private {struct msm_drm_thread* event_thread; } ;
struct drm_encoder {TYPE_2__* crtc; TYPE_1__* dev; } ;
struct dpu_encoder_virt {int /*<<< orphan*/  vsync_event_timer; struct drm_encoder base; } ;
struct TYPE_4__ {size_t index; } ;
struct TYPE_3__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct msm_drm_thread*) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 struct dpu_encoder_virt* dpu_enc ; 
 struct dpu_encoder_virt* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsync_event_timer ; 

__attribute__((used)) static void dpu_encoder_vsync_event_handler(struct timer_list *t)
{
	struct dpu_encoder_virt *dpu_enc = from_timer(dpu_enc, t,
			vsync_event_timer);
	struct drm_encoder *drm_enc = &dpu_enc->base;
	struct msm_drm_private *priv;
	struct msm_drm_thread *event_thread;

	if (!drm_enc->dev || !drm_enc->dev->dev_private ||
			!drm_enc->crtc) {
		DPU_ERROR("invalid parameters\n");
		return;
	}

	priv = drm_enc->dev->dev_private;

	if (drm_enc->crtc->index >= ARRAY_SIZE(priv->event_thread)) {
		DPU_ERROR("invalid crtc index\n");
		return;
	}
	event_thread = &priv->event_thread[drm_enc->crtc->index];
	if (!event_thread) {
		DPU_ERROR("event_thread not found for crtc:%d\n",
				drm_enc->crtc->index);
		return;
	}

	del_timer(&dpu_enc->vsync_event_timer);
}