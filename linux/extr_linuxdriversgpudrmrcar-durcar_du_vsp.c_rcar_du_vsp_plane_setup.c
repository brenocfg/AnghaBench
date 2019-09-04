#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int left; int top; int width; int height; } ;
struct TYPE_12__ {int left; int top; int width; int height; } ;
struct vsp1_du_atomic_config {int alpha; int /*<<< orphan*/  pixelformat; scalar_t__* mem; TYPE_3__ dst; TYPE_2__ src; int /*<<< orphan*/  zpos; int /*<<< orphan*/  pitch; } ;
struct TYPE_19__ {int x1; int y1; } ;
struct TYPE_14__ {int alpha; TYPE_9__ dst; TYPE_9__ src; int /*<<< orphan*/  zpos; int /*<<< orphan*/  crtc; } ;
struct rcar_du_vsp_plane_state {TYPE_6__* format; TYPE_5__* sg_tables; TYPE_4__ state; } ;
struct TYPE_11__ {TYPE_8__* state; } ;
struct rcar_du_vsp_plane {int /*<<< orphan*/  index; TYPE_7__* vsp; TYPE_1__ plane; } ;
struct rcar_du_crtc {int /*<<< orphan*/  vsp_pipe; } ;
struct drm_framebuffer {scalar_t__* offsets; int /*<<< orphan*/ * pitches; } ;
struct TYPE_18__ {struct drm_framebuffer* fb; } ;
struct TYPE_17__ {int /*<<< orphan*/  vsp; } ;
struct TYPE_16__ {unsigned int planes; scalar_t__ fourcc; } ;
struct TYPE_15__ {int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 int drm_rect_height (TYPE_9__*) ; 
 int drm_rect_width (TYPE_9__*) ; 
 scalar_t__* formats_kms ; 
 int /*<<< orphan*/ * formats_v4l2 ; 
 scalar_t__ sg_dma_address (int /*<<< orphan*/ ) ; 
 struct rcar_du_crtc* to_rcar_crtc (int /*<<< orphan*/ ) ; 
 struct rcar_du_vsp_plane_state* to_rcar_vsp_plane_state (TYPE_8__*) ; 
 int /*<<< orphan*/  vsp1_du_atomic_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vsp1_du_atomic_config*) ; 

__attribute__((used)) static void rcar_du_vsp_plane_setup(struct rcar_du_vsp_plane *plane)
{
	struct rcar_du_vsp_plane_state *state =
		to_rcar_vsp_plane_state(plane->plane.state);
	struct rcar_du_crtc *crtc = to_rcar_crtc(state->state.crtc);
	struct drm_framebuffer *fb = plane->plane.state->fb;
	struct vsp1_du_atomic_config cfg = {
		.pixelformat = 0,
		.pitch = fb->pitches[0],
		.alpha = state->state.alpha >> 8,
		.zpos = state->state.zpos,
	};
	unsigned int i;

	cfg.src.left = state->state.src.x1 >> 16;
	cfg.src.top = state->state.src.y1 >> 16;
	cfg.src.width = drm_rect_width(&state->state.src) >> 16;
	cfg.src.height = drm_rect_height(&state->state.src) >> 16;

	cfg.dst.left = state->state.dst.x1;
	cfg.dst.top = state->state.dst.y1;
	cfg.dst.width = drm_rect_width(&state->state.dst);
	cfg.dst.height = drm_rect_height(&state->state.dst);

	for (i = 0; i < state->format->planes; ++i)
		cfg.mem[i] = sg_dma_address(state->sg_tables[i].sgl)
			   + fb->offsets[i];

	for (i = 0; i < ARRAY_SIZE(formats_kms); ++i) {
		if (formats_kms[i] == state->format->fourcc) {
			cfg.pixelformat = formats_v4l2[i];
			break;
		}
	}

	vsp1_du_atomic_update(plane->vsp->vsp, crtc->vsp_pipe,
			      plane->index, &cfg);
}