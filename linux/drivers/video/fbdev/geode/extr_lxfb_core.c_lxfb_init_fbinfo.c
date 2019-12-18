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
typedef  int /*<<< orphan*/  u32 ;
struct lxfb_par {int dummy; } ;
struct TYPE_4__ {int height; int width; scalar_t__ grayscale; int /*<<< orphan*/  vmode; scalar_t__ accel_flags; int /*<<< orphan*/  activate; scalar_t__ nonstd; } ;
struct TYPE_3__ {int /*<<< orphan*/  accel; scalar_t__ ywrapstep; scalar_t__ ypanstep; scalar_t__ xpanstep; scalar_t__ type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct fb_info {int node; TYPE_2__ var; int /*<<< orphan*/  cmap; void* pseudo_palette; int /*<<< orphan*/  flags; int /*<<< orphan*/ * fbops; TYPE_1__ fix; struct lxfb_par* par; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBINFO_DEFAULT ; 
 int /*<<< orphan*/  FB_ACCEL_NONE ; 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VMODE_NONINTERLACED ; 
 scalar_t__ fb_alloc_cmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct fb_info* framebuffer_alloc (int,struct device*) ; 
 int /*<<< orphan*/  framebuffer_release (struct fb_info*) ; 
 int /*<<< orphan*/  lxfb_ops ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct fb_info *lxfb_init_fbinfo(struct device *dev)
{
	struct lxfb_par *par;
	struct fb_info *info;

	/* Alloc enough space for the pseudo palette. */
	info = framebuffer_alloc(sizeof(struct lxfb_par) + sizeof(u32) * 16,
				 dev);
	if (!info)
		return NULL;

	par = info->par;

	strcpy(info->fix.id, "Geode LX");

	info->fix.type		= FB_TYPE_PACKED_PIXELS;
	info->fix.type_aux	= 0;
	info->fix.xpanstep	= 0;
	info->fix.ypanstep	= 0;
	info->fix.ywrapstep	= 0;
	info->fix.accel		= FB_ACCEL_NONE;

	info->var.nonstd	= 0;
	info->var.activate	= FB_ACTIVATE_NOW;
	info->var.height	= -1;
	info->var.width	= -1;
	info->var.accel_flags = 0;
	info->var.vmode	= FB_VMODE_NONINTERLACED;

	info->fbops		= &lxfb_ops;
	info->flags		= FBINFO_DEFAULT;
	info->node		= -1;

	info->pseudo_palette	= (void *)par + sizeof(struct lxfb_par);

	if (fb_alloc_cmap(&info->cmap, 256, 0) < 0) {
		framebuffer_release(info);
		return NULL;
	}

	info->var.grayscale	= 0;

	return info;
}