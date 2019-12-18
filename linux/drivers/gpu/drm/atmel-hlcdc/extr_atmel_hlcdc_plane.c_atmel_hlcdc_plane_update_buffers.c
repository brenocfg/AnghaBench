#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_gem_cma_object {scalar_t__ paddr; } ;
struct drm_framebuffer {int dummy; } ;
struct TYPE_7__ {struct drm_framebuffer* fb; } ;
struct atmel_hlcdc_plane_state {int nplanes; int /*<<< orphan*/ * pstride; int /*<<< orphan*/ * xstride; TYPE_2__** dscrs; scalar_t__* offsets; TYPE_1__ base; } ;
struct TYPE_10__ {struct atmel_hlcdc_layer_desc* desc; } ;
struct atmel_hlcdc_plane {TYPE_4__ layer; } ;
struct TYPE_9__ {scalar_t__* pstride; scalar_t__* xstride; } ;
struct atmel_hlcdc_layer_desc {TYPE_3__ layout; } ;
struct TYPE_8__ {scalar_t__ self; scalar_t__ ctrl; scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_HLCDC_LAYER_CHSR ; 
 int ATMEL_HLCDC_LAYER_EN ; 
 int /*<<< orphan*/  ATMEL_HLCDC_LAYER_PLANE_ADDR (int) ; 
 int /*<<< orphan*/  ATMEL_HLCDC_LAYER_PLANE_CTRL (int) ; 
 int /*<<< orphan*/  ATMEL_HLCDC_LAYER_PLANE_HEAD (int) ; 
 int /*<<< orphan*/  ATMEL_HLCDC_LAYER_PLANE_NEXT (int) ; 
 int atmel_hlcdc_layer_read_reg (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_hlcdc_layer_write_cfg (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_hlcdc_layer_write_reg (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct drm_gem_cma_object* drm_fb_cma_get_gem_obj (struct drm_framebuffer*,int) ; 

__attribute__((used)) static void atmel_hlcdc_plane_update_buffers(struct atmel_hlcdc_plane *plane,
					struct atmel_hlcdc_plane_state *state)
{
	const struct atmel_hlcdc_layer_desc *desc = plane->layer.desc;
	struct drm_framebuffer *fb = state->base.fb;
	u32 sr;
	int i;

	sr = atmel_hlcdc_layer_read_reg(&plane->layer, ATMEL_HLCDC_LAYER_CHSR);

	for (i = 0; i < state->nplanes; i++) {
		struct drm_gem_cma_object *gem = drm_fb_cma_get_gem_obj(fb, i);

		state->dscrs[i]->addr = gem->paddr + state->offsets[i];

		atmel_hlcdc_layer_write_reg(&plane->layer,
					    ATMEL_HLCDC_LAYER_PLANE_HEAD(i),
					    state->dscrs[i]->self);

		if (!(sr & ATMEL_HLCDC_LAYER_EN)) {
			atmel_hlcdc_layer_write_reg(&plane->layer,
					ATMEL_HLCDC_LAYER_PLANE_ADDR(i),
					state->dscrs[i]->addr);
			atmel_hlcdc_layer_write_reg(&plane->layer,
					ATMEL_HLCDC_LAYER_PLANE_CTRL(i),
					state->dscrs[i]->ctrl);
			atmel_hlcdc_layer_write_reg(&plane->layer,
					ATMEL_HLCDC_LAYER_PLANE_NEXT(i),
					state->dscrs[i]->self);
		}

		if (desc->layout.xstride[i])
			atmel_hlcdc_layer_write_cfg(&plane->layer,
						    desc->layout.xstride[i],
						    state->xstride[i]);

		if (desc->layout.pstride[i])
			atmel_hlcdc_layer_write_cfg(&plane->layer,
						    desc->layout.pstride[i],
						    state->pstride[i]);
	}
}