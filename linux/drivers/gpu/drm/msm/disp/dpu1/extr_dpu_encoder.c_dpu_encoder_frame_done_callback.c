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
typedef  int u32 ;
struct drm_encoder {int dummy; } ;
struct dpu_encoder_virt {unsigned int num_phys_encs; int /*<<< orphan*/  crtc_frame_event_cb_data; int /*<<< orphan*/  (* crtc_frame_event_cb ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  frame_done_timer; int /*<<< orphan*/  frame_done_timeout_ms; int /*<<< orphan*/ * frame_busy_mask; struct dpu_encoder_phys** phys_encs; } ;
struct dpu_encoder_phys {int /*<<< orphan*/  intf_idx; } ;

/* Variables and functions */
 int DPU_ENCODER_FRAME_EVENT_DONE ; 
 int DPU_ENCODER_FRAME_EVENT_ERROR ; 
 int DPU_ENCODER_FRAME_EVENT_PANEL_DEAD ; 
 int /*<<< orphan*/  DPU_ENC_RC_EVENT_FRAME_DONE ; 
 int /*<<< orphan*/  DRMID (struct drm_encoder*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpu_encoder_resource_control (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 struct dpu_encoder_virt* to_dpu_encoder_virt (struct drm_encoder*) ; 
 int /*<<< orphan*/  trace_dpu_enc_frame_done_cb (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dpu_enc_frame_done_cb_not_busy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpu_encoder_frame_done_callback(
		struct drm_encoder *drm_enc,
		struct dpu_encoder_phys *ready_phys, u32 event)
{
	struct dpu_encoder_virt *dpu_enc = to_dpu_encoder_virt(drm_enc);
	unsigned int i;

	if (event & (DPU_ENCODER_FRAME_EVENT_DONE
			| DPU_ENCODER_FRAME_EVENT_ERROR
			| DPU_ENCODER_FRAME_EVENT_PANEL_DEAD)) {

		if (!dpu_enc->frame_busy_mask[0]) {
			/**
			 * suppress frame_done without waiter,
			 * likely autorefresh
			 */
			trace_dpu_enc_frame_done_cb_not_busy(DRMID(drm_enc),
					event, ready_phys->intf_idx);
			return;
		}

		/* One of the physical encoders has become idle */
		for (i = 0; i < dpu_enc->num_phys_encs; i++) {
			if (dpu_enc->phys_encs[i] == ready_phys) {
				trace_dpu_enc_frame_done_cb(DRMID(drm_enc), i,
						dpu_enc->frame_busy_mask[0]);
				clear_bit(i, dpu_enc->frame_busy_mask);
			}
		}

		if (!dpu_enc->frame_busy_mask[0]) {
			atomic_set(&dpu_enc->frame_done_timeout_ms, 0);
			del_timer(&dpu_enc->frame_done_timer);

			dpu_encoder_resource_control(drm_enc,
					DPU_ENC_RC_EVENT_FRAME_DONE);

			if (dpu_enc->crtc_frame_event_cb)
				dpu_enc->crtc_frame_event_cb(
					dpu_enc->crtc_frame_event_cb_data,
					event);
		}
	} else {
		if (dpu_enc->crtc_frame_event_cb)
			dpu_enc->crtc_frame_event_cb(
				dpu_enc->crtc_frame_event_cb_data, event);
	}
}