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
struct vsp1_du_writeback_config {scalar_t__* mem; int /*<<< orphan*/  pitch; int /*<<< orphan*/  pixelformat; } ;
struct rcar_du_wb_job {TYPE_4__* sg_tables; } ;
struct rcar_du_wb_conn_state {TYPE_3__* format; } ;
struct TYPE_6__ {struct drm_connector_state* state; } ;
struct TYPE_10__ {TYPE_1__ base; } ;
struct rcar_du_crtc {TYPE_5__ writeback; } ;
struct drm_framebuffer {scalar_t__* offsets; int /*<<< orphan*/ * pitches; } ;
struct drm_connector_state {TYPE_2__* writeback_job; } ;
struct TYPE_9__ {int /*<<< orphan*/  sgl; } ;
struct TYPE_8__ {unsigned int planes; int /*<<< orphan*/  v4l2; } ;
struct TYPE_7__ {struct rcar_du_wb_job* priv; struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_writeback_queue_job (TYPE_5__*,struct drm_connector_state*) ; 
 scalar_t__ sg_dma_address (int /*<<< orphan*/ ) ; 
 struct rcar_du_wb_conn_state* to_rcar_wb_conn_state (struct drm_connector_state*) ; 

void rcar_du_writeback_setup(struct rcar_du_crtc *rcrtc,
			     struct vsp1_du_writeback_config *cfg)
{
	struct rcar_du_wb_conn_state *wb_state;
	struct drm_connector_state *state;
	struct rcar_du_wb_job *rjob;
	struct drm_framebuffer *fb;
	unsigned int i;

	state = rcrtc->writeback.base.state;
	if (!state || !state->writeback_job)
		return;

	fb = state->writeback_job->fb;
	rjob = state->writeback_job->priv;
	wb_state = to_rcar_wb_conn_state(state);

	cfg->pixelformat = wb_state->format->v4l2;
	cfg->pitch = fb->pitches[0];

	for (i = 0; i < wb_state->format->planes; ++i)
		cfg->mem[i] = sg_dma_address(rjob->sg_tables[i].sgl)
			    + fb->offsets[i];

	drm_writeback_queue_job(&rcrtc->writeback, state);
}