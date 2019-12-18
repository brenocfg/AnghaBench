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
struct rcar_du_vsp {int /*<<< orphan*/  vsp; struct rcar_du_device* dev; } ;
struct rcar_du_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct drm_gem_cma_object {TYPE_2__ base; int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; } ;
struct drm_framebuffer {TYPE_1__* format; } ;
struct TYPE_3__ {unsigned int num_planes; } ;

/* Variables and functions */
 int ENOMEM ; 
 int dma_get_sgtable (int /*<<< orphan*/ ,struct sg_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_gem_cma_object* drm_fb_cma_get_gem_obj (struct drm_framebuffer*,unsigned int) ; 
 int /*<<< orphan*/  sg_free_table (struct sg_table*) ; 
 int vsp1_du_map_sg (int /*<<< orphan*/ ,struct sg_table*) ; 
 int /*<<< orphan*/  vsp1_du_unmap_sg (int /*<<< orphan*/ ,struct sg_table*) ; 

int rcar_du_vsp_map_fb(struct rcar_du_vsp *vsp, struct drm_framebuffer *fb,
		       struct sg_table sg_tables[3])
{
	struct rcar_du_device *rcdu = vsp->dev;
	unsigned int i;
	int ret;

	for (i = 0; i < fb->format->num_planes; ++i) {
		struct drm_gem_cma_object *gem = drm_fb_cma_get_gem_obj(fb, i);
		struct sg_table *sgt = &sg_tables[i];

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

	return 0;

fail:
	while (i--) {
		struct sg_table *sgt = &sg_tables[i];

		vsp1_du_unmap_sg(vsp->vsp, sgt);
		sg_free_table(sgt);
	}

	return ret;
}