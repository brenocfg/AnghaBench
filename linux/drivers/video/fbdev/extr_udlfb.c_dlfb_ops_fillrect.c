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
struct fb_info {struct dlfb_data* par; } ;
struct fb_fillrect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;
struct dlfb_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlfb_offload_damage (struct dlfb_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_fillrect (struct fb_info*,struct fb_fillrect const*) ; 

__attribute__((used)) static void dlfb_ops_fillrect(struct fb_info *info,
			  const struct fb_fillrect *rect)
{
	struct dlfb_data *dlfb = info->par;

	sys_fillrect(info, rect);

	dlfb_offload_damage(dlfb, rect->dx, rect->dy, rect->width,
			      rect->height);
}