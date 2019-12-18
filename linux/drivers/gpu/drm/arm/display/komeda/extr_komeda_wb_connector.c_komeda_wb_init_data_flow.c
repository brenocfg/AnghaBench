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
struct TYPE_10__ {TYPE_4__* pipeline; } ;
struct komeda_layer {TYPE_5__ base; } ;
struct TYPE_7__ {int /*<<< orphan*/ * component; } ;
struct komeda_data_flow_cfg {int /*<<< orphan*/  rot; int /*<<< orphan*/  pixel_blend_mode; TYPE_2__ input; int /*<<< orphan*/  in_h; int /*<<< orphan*/  in_w; int /*<<< orphan*/  out_h; int /*<<< orphan*/  out_w; } ;
struct komeda_crtc_state {int dummy; } ;
struct drm_framebuffer {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_connector_state {TYPE_1__* writeback_job; } ;
struct TYPE_9__ {TYPE_3__* compiz; } ;
struct TYPE_8__ {int /*<<< orphan*/  base; } ;
struct TYPE_6__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_BLEND_PIXEL_NONE ; 
 int /*<<< orphan*/  DRM_MODE_ROTATE_0 ; 
 int /*<<< orphan*/  komeda_complete_data_flow_cfg (struct komeda_layer*,struct komeda_data_flow_cfg*,struct drm_framebuffer*) ; 
 int /*<<< orphan*/  memset (struct komeda_data_flow_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pipeline_composition_size (struct komeda_crtc_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
komeda_wb_init_data_flow(struct komeda_layer *wb_layer,
			 struct drm_connector_state *conn_st,
			 struct komeda_crtc_state *kcrtc_st,
			 struct komeda_data_flow_cfg *dflow)
{
	struct drm_framebuffer *fb = conn_st->writeback_job->fb;

	memset(dflow, 0, sizeof(*dflow));

	dflow->out_w = fb->width;
	dflow->out_h = fb->height;

	/* the write back data comes from the compiz */
	pipeline_composition_size(kcrtc_st, &dflow->in_w, &dflow->in_h);
	dflow->input.component = &wb_layer->base.pipeline->compiz->base;
	/* compiz doesn't output alpha */
	dflow->pixel_blend_mode = DRM_MODE_BLEND_PIXEL_NONE;
	dflow->rot = DRM_MODE_ROTATE_0;

	komeda_complete_data_flow_cfg(wb_layer, dflow, fb);

	return 0;
}