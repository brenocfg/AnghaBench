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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct nouveau_fbdev {TYPE_1__ helper; } ;
struct nouveau_drm {struct nouveau_channel* channel; } ;
struct nouveau_channel {int dummy; } ;
struct fb_info {struct nouveau_fbdev* par; } ;
struct fb_copyarea {int sy; int sx; int dy; int dx; int height; int width; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_NV04 (struct nouveau_channel*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  FIRE_RING (struct nouveau_channel*) ; 
 int /*<<< orphan*/  NvSubImageBlit ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 

int
nv04_fbcon_copyarea(struct fb_info *info, const struct fb_copyarea *region)
{
	struct nouveau_fbdev *nfbdev = info->par;
	struct nouveau_drm *drm = nouveau_drm(nfbdev->helper.dev);
	struct nouveau_channel *chan = drm->channel;
	int ret;

	ret = RING_SPACE(chan, 4);
	if (ret)
		return ret;

	BEGIN_NV04(chan, NvSubImageBlit, 0x0300, 3);
	OUT_RING(chan, (region->sy << 16) | region->sx);
	OUT_RING(chan, (region->dy << 16) | region->dx);
	OUT_RING(chan, (region->height << 16) | region->width);
	FIRE_RING(chan);
	return 0;
}