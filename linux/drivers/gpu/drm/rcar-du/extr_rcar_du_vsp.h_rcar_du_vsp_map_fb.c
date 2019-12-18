#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sg_table {int dummy; } ;
struct rcar_du_vsp {int dummy; } ;
struct drm_framebuffer {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 

__attribute__((used)) static inline int rcar_du_vsp_map_fb(struct rcar_du_vsp *vsp,
				     struct drm_framebuffer *fb,
				     struct sg_table sg_tables[3])
{
	return -ENXIO;
}