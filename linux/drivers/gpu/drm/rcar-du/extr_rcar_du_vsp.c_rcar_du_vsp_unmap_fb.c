#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sg_table {int dummy; } ;
struct rcar_du_vsp {int /*<<< orphan*/  vsp; } ;
struct drm_framebuffer {TYPE_1__* format; } ;
struct TYPE_2__ {unsigned int num_planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_free_table (struct sg_table*) ; 
 int /*<<< orphan*/  vsp1_du_unmap_sg (int /*<<< orphan*/ ,struct sg_table*) ; 

void rcar_du_vsp_unmap_fb(struct rcar_du_vsp *vsp, struct drm_framebuffer *fb,
			  struct sg_table sg_tables[3])
{
	unsigned int i;

	for (i = 0; i < fb->format->num_planes; ++i) {
		struct sg_table *sgt = &sg_tables[i];

		vsp1_du_unmap_sg(vsp->vsp, sgt);
		sg_free_table(sgt);
	}
}