#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sg_table {int dummy; } ;
struct rcar_du_vsp_plane_state {struct sg_table* sg_tables; TYPE_1__* format; } ;
struct rcar_du_vsp {int /*<<< orphan*/  vsp; struct rcar_du_device* dev; } ;
struct rcar_du_device {int /*<<< orphan*/  dev; } ;
struct drm_plane_state {int /*<<< orphan*/  fb; int /*<<< orphan*/  visible; } ;
struct drm_plane {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;
struct drm_gem_cma_object {TYPE_2__ base; int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; } ;
struct TYPE_6__ {struct rcar_du_vsp* vsp; } ;
struct TYPE_4__ {unsigned int planes; } ;

/* Variables and functions */
 int ENOMEM ; 
 int dma_get_sgtable (int /*<<< orphan*/ ,struct sg_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_gem_cma_object* drm_fb_cma_get_gem_obj (int /*<<< orphan*/ ,unsigned int) ; 
 int drm_gem_fb_prepare_fb (struct drm_plane*,struct drm_plane_state*) ; 
 int /*<<< orphan*/  sg_free_table (struct sg_table*) ; 
 TYPE_3__* to_rcar_vsp_plane (struct drm_plane*) ; 
 struct rcar_du_vsp_plane_state* to_rcar_vsp_plane_state (struct drm_plane_state*) ; 
 int vsp1_du_map_sg (int /*<<< orphan*/ ,struct sg_table*) ; 
 int /*<<< orphan*/  vsp1_du_unmap_sg (int /*<<< orphan*/ ,struct sg_table*) ; 

__attribute__((used)) static int rcar_du_vsp_plane_prepare_fb(struct drm_plane *plane,
					struct drm_plane_state *state)
{
	struct rcar_du_vsp_plane_state *rstate = to_rcar_vsp_plane_state(state);
	struct rcar_du_vsp *vsp = to_rcar_vsp_plane(plane)->vsp;
	struct rcar_du_device *rcdu = vsp->dev;
	unsigned int i;
	int ret;

	/*
	 * There's no need to prepare (and unprepare) the framebuffer when the
	 * plane is not visible, as it will not be displayed.
	 */
	if (!state->visible)
		return 0;

	for (i = 0; i < rstate->format->planes; ++i) {
		struct drm_gem_cma_object *gem =
			drm_fb_cma_get_gem_obj(state->fb, i);
		struct sg_table *sgt = &rstate->sg_tables[i];

		ret = dma_get_sgtable(rcdu->dev, sgt, gem->vaddr, gem->paddr,
				      gem->base.size);
		if (ret)
			goto fail;

		ret = vsp1_du_map_sg(vsp->vsp, sgt);
		if (!ret) {
			sg_free_table(sgt);
			ret = -ENOMEM;
			goto fail;
		}
	}

	ret = drm_gem_fb_prepare_fb(plane, state);
	if (ret)
		goto fail;

	return 0;

fail:
	while (i--) {
		struct sg_table *sgt = &rstate->sg_tables[i];

		vsp1_du_unmap_sg(vsp->vsp, sgt);
		sg_free_table(sgt);
	}

	return ret;
}