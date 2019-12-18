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
typedef  int u32 ;
struct drm_encoder {TYPE_2__* crtc; } ;
struct drm_display_mode {int vtotal; } ;
struct dpu_encoder_virt {TYPE_4__* cur_master; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_7__ {int (* get_line_count ) (TYPE_4__*) ;} ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct TYPE_6__ {TYPE_1__* state; } ;
struct TYPE_5__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_ENC (struct dpu_encoder_virt*,char*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPU_ERROR (char*,...) ; 
 int EINVAL ; 
 int _dpu_encoder_calculate_linetime (struct dpu_encoder_virt*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_to_ms (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_4__*) ; 
 struct dpu_encoder_virt* to_dpu_encoder_virt (struct drm_encoder*) ; 

int dpu_encoder_vsync_time(struct drm_encoder *drm_enc, ktime_t *wakeup_time)
{
	struct drm_display_mode *mode;
	struct dpu_encoder_virt *dpu_enc;
	u32 cur_line;
	u32 line_time;
	u32 vtotal, time_to_vsync;
	ktime_t cur_time;

	dpu_enc = to_dpu_encoder_virt(drm_enc);

	if (!drm_enc->crtc || !drm_enc->crtc->state) {
		DPU_ERROR("crtc/crtc state object is NULL\n");
		return -EINVAL;
	}
	mode = &drm_enc->crtc->state->adjusted_mode;

	line_time = _dpu_encoder_calculate_linetime(dpu_enc, mode);
	if (!line_time)
		return -EINVAL;

	cur_line = dpu_enc->cur_master->ops.get_line_count(dpu_enc->cur_master);

	vtotal = mode->vtotal;
	if (cur_line >= vtotal)
		time_to_vsync = line_time * vtotal;
	else
		time_to_vsync = line_time * (vtotal - cur_line);

	if (time_to_vsync == 0) {
		DPU_ERROR("time to vsync should not be zero, vtotal=%d\n",
				vtotal);
		return -EINVAL;
	}

	cur_time = ktime_get();
	*wakeup_time = ktime_add_ns(cur_time, time_to_vsync);

	DPU_DEBUG_ENC(dpu_enc,
			"cur_line=%u vtotal=%u time_to_vsync=%u, cur_time=%lld, wakeup_time=%lld\n",
			cur_line, vtotal, time_to_vsync,
			ktime_to_ms(cur_time),
			ktime_to_ms(*wakeup_time));
	return 0;
}