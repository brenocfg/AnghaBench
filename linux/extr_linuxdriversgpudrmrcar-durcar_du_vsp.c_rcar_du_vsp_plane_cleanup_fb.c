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
struct sg_table {int dummy; } ;
struct rcar_du_vsp_plane_state {struct sg_table* sg_tables; TYPE_1__* format; } ;
struct rcar_du_vsp {int /*<<< orphan*/  vsp; } ;
struct drm_plane_state {int /*<<< orphan*/  visible; } ;
struct drm_plane {int dummy; } ;
struct TYPE_4__ {struct rcar_du_vsp* vsp; } ;
struct TYPE_3__ {unsigned int planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_free_table (struct sg_table*) ; 
 TYPE_2__* to_rcar_vsp_plane (struct drm_plane*) ; 
 struct rcar_du_vsp_plane_state* to_rcar_vsp_plane_state (struct drm_plane_state*) ; 
 int /*<<< orphan*/  vsp1_du_unmap_sg (int /*<<< orphan*/ ,struct sg_table*) ; 

__attribute__((used)) static void rcar_du_vsp_plane_cleanup_fb(struct drm_plane *plane,
					 struct drm_plane_state *state)
{
	struct rcar_du_vsp_plane_state *rstate = to_rcar_vsp_plane_state(state);
	struct rcar_du_vsp *vsp = to_rcar_vsp_plane(plane)->vsp;
	unsigned int i;

	if (!state->visible)
		return;

	for (i = 0; i < rstate->format->planes; ++i) {
		struct sg_table *sgt = &rstate->sg_tables[i];

		vsp1_du_unmap_sg(vsp->vsp, sgt);
		sg_free_table(sgt);
	}
}