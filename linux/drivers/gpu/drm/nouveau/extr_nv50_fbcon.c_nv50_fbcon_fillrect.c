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
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct nouveau_fbdev {TYPE_1__ helper; } ;
struct nouveau_drm {struct nouveau_channel* channel; } ;
struct nouveau_channel {int dummy; } ;
struct TYPE_4__ {scalar_t__ visual; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_2__ fix; struct nouveau_fbdev* par; } ;
struct fb_fillrect {scalar_t__ rop; size_t color; int dx; int dy; int width; int height; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_NV04 (struct nouveau_channel*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ FB_VISUAL_DIRECTCOLOR ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  FIRE_RING (struct nouveau_channel*) ; 
 int /*<<< orphan*/  NvSub2D ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 
 scalar_t__ ROP_COPY ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 

int
nv50_fbcon_fillrect(struct fb_info *info, const struct fb_fillrect *rect)
{
	struct nouveau_fbdev *nfbdev = info->par;
	struct nouveau_drm *drm = nouveau_drm(nfbdev->helper.dev);
	struct nouveau_channel *chan = drm->channel;
	int ret;

	ret = RING_SPACE(chan, rect->rop == ROP_COPY ? 7 : 11);
	if (ret)
		return ret;

	if (rect->rop != ROP_COPY) {
		BEGIN_NV04(chan, NvSub2D, 0x02ac, 1);
		OUT_RING(chan, 1);
	}
	BEGIN_NV04(chan, NvSub2D, 0x0588, 1);
	if (info->fix.visual == FB_VISUAL_TRUECOLOR ||
	    info->fix.visual == FB_VISUAL_DIRECTCOLOR)
		OUT_RING(chan, ((uint32_t *)info->pseudo_palette)[rect->color]);
	else
		OUT_RING(chan, rect->color);
	BEGIN_NV04(chan, NvSub2D, 0x0600, 4);
	OUT_RING(chan, rect->dx);
	OUT_RING(chan, rect->dy);
	OUT_RING(chan, rect->dx + rect->width);
	OUT_RING(chan, rect->dy + rect->height);
	if (rect->rop != ROP_COPY) {
		BEGIN_NV04(chan, NvSub2D, 0x02ac, 1);
		OUT_RING(chan, 3);
	}
	FIRE_RING(chan);
	return 0;
}