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
typedef  int /*<<< orphan*/  u16 ;
struct fb_info {struct drm_fb_helper* par; } ;
struct fb_cmap {scalar_t__ start; int len; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct drm_fb_helper {int crtc_count; int /*<<< orphan*/  dev; TYPE_2__* crtc_info; } ;
struct drm_crtc {scalar_t__ gamma_size; TYPE_3__* funcs; int /*<<< orphan*/ * gamma_store; } ;
struct TYPE_6__ {int (* gamma_set ) (struct drm_crtc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {struct drm_crtc* crtc; } ;
struct TYPE_5__ {TYPE_1__ mode_set; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  drm_modeset_lock_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct drm_crtc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setcmap_legacy(struct fb_cmap *cmap, struct fb_info *info)
{
	struct drm_fb_helper *fb_helper = info->par;
	struct drm_crtc *crtc;
	u16 *r, *g, *b;
	int i, ret = 0;

	drm_modeset_lock_all(fb_helper->dev);
	for (i = 0; i < fb_helper->crtc_count; i++) {
		crtc = fb_helper->crtc_info[i].mode_set.crtc;
		if (!crtc->funcs->gamma_set || !crtc->gamma_size)
			return -EINVAL;

		if (cmap->start + cmap->len > crtc->gamma_size)
			return -EINVAL;

		r = crtc->gamma_store;
		g = r + crtc->gamma_size;
		b = g + crtc->gamma_size;

		memcpy(r + cmap->start, cmap->red, cmap->len * sizeof(*r));
		memcpy(g + cmap->start, cmap->green, cmap->len * sizeof(*g));
		memcpy(b + cmap->start, cmap->blue, cmap->len * sizeof(*b));

		ret = crtc->funcs->gamma_set(crtc, r, g, b,
					     crtc->gamma_size, NULL);
		if (ret)
			return ret;
	}
	drm_modeset_unlock_all(fb_helper->dev);

	return ret;
}