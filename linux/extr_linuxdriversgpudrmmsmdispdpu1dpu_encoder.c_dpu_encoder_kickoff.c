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
struct drm_encoder {TYPE_3__* crtc; } ;
struct TYPE_10__ {scalar_t__ intf_type; } ;
struct dpu_encoder_virt {unsigned int num_phys_encs; int /*<<< orphan*/  vsync_event_timer; TYPE_5__ disp_info; struct dpu_encoder_phys** phys_encs; int /*<<< orphan*/  frame_done_timeout; int /*<<< orphan*/  frame_done_timer; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* handle_post_kickoff ) (struct dpu_encoder_phys*) ;} ;
struct dpu_encoder_phys {TYPE_4__ ops; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_8__ {TYPE_2__* state; } ;
struct TYPE_6__ {int vrefresh; } ;
struct TYPE_7__ {TYPE_1__ adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ATRACE_BEGIN (char*) ; 
 int /*<<< orphan*/  DPU_ATRACE_END (char*) ; 
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int DPU_FRAME_DONE_TIMEOUT ; 
 int /*<<< orphan*/  DRMID (struct drm_encoder*) ; 
 scalar_t__ DRM_MODE_CONNECTOR_DSI ; 
 int HZ ; 
 int /*<<< orphan*/  _dpu_encoder_kickoff_phys (struct dpu_encoder_virt*) ; 
 int /*<<< orphan*/  _dpu_encoder_wakeup_time (struct drm_encoder*,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  ktime_to_ms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ nsecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dpu_encoder_phys*) ; 
 struct dpu_encoder_virt* to_dpu_encoder_virt (struct drm_encoder*) ; 
 int /*<<< orphan*/  trace_dpu_enc_early_kickoff (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dpu_enc_kickoff (int /*<<< orphan*/ ) ; 

void dpu_encoder_kickoff(struct drm_encoder *drm_enc)
{
	struct dpu_encoder_virt *dpu_enc;
	struct dpu_encoder_phys *phys;
	ktime_t wakeup_time;
	unsigned int i;

	if (!drm_enc) {
		DPU_ERROR("invalid encoder\n");
		return;
	}
	DPU_ATRACE_BEGIN("encoder_kickoff");
	dpu_enc = to_dpu_encoder_virt(drm_enc);

	trace_dpu_enc_kickoff(DRMID(drm_enc));

	atomic_set(&dpu_enc->frame_done_timeout,
			DPU_FRAME_DONE_TIMEOUT * 1000 /
			drm_enc->crtc->state->adjusted_mode.vrefresh);
	mod_timer(&dpu_enc->frame_done_timer, jiffies +
		((atomic_read(&dpu_enc->frame_done_timeout) * HZ) / 1000));

	/* All phys encs are ready to go, trigger the kickoff */
	_dpu_encoder_kickoff_phys(dpu_enc);

	/* allow phys encs to handle any post-kickoff business */
	for (i = 0; i < dpu_enc->num_phys_encs; i++) {
		phys = dpu_enc->phys_encs[i];
		if (phys && phys->ops.handle_post_kickoff)
			phys->ops.handle_post_kickoff(phys);
	}

	if (dpu_enc->disp_info.intf_type == DRM_MODE_CONNECTOR_DSI &&
			!_dpu_encoder_wakeup_time(drm_enc, &wakeup_time)) {
		trace_dpu_enc_early_kickoff(DRMID(drm_enc),
					    ktime_to_ms(wakeup_time));
		mod_timer(&dpu_enc->vsync_event_timer,
				nsecs_to_jiffies(ktime_to_ns(wakeup_time)));
	}

	DPU_ATRACE_END("encoder_kickoff");
}