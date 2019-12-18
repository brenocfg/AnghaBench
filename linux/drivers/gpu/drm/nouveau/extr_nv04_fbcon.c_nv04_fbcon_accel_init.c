#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ family; int chipset; } ;
struct nvif_device {TYPE_4__ info; } ;
struct TYPE_18__ {int handle; } ;
struct TYPE_10__ {struct drm_device* dev; } ;
struct nouveau_fbdev {TYPE_9__ rop; TYPE_9__ patt; TYPE_9__ surf2d; TYPE_9__ gdi; TYPE_9__ blit; TYPE_9__ clip; TYPE_1__ helper; } ;
struct TYPE_11__ {struct nvif_device device; } ;
struct nouveau_drm {TYPE_2__ client; struct nouveau_channel* channel; } ;
struct TYPE_14__ {int handle; } ;
struct nouveau_channel {TYPE_5__ vram; int /*<<< orphan*/  user; } ;
struct TYPE_12__ {int /*<<< orphan*/  length; } ;
struct TYPE_17__ {int bits_per_pixel; int yres_virtual; int xres_virtual; TYPE_3__ transp; } ;
struct TYPE_15__ {int line_length; int smem_start; } ;
struct fb_info {TYPE_8__ var; TYPE_6__ fix; struct nouveau_fbdev* par; } ;
struct TYPE_16__ {int fb_base; } ;
struct drm_device {TYPE_7__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_NV04 (struct nouveau_channel*,int /*<<< orphan*/ ,int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FIRE_RING (struct nouveau_channel*) ; 
 scalar_t__ NV_DEVICE_INFO_V0_CELSIUS ; 
 int /*<<< orphan*/  NvSubCtxSurf2D ; 
 int /*<<< orphan*/  NvSubGdiRect ; 
 int /*<<< orphan*/  NvSubImageBlit ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 scalar_t__ RING_SPACE (struct nouveau_channel*,int) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_fbcon_gpu_lockup (struct fb_info*) ; 
 int nvif_object_init (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_9__*) ; 

int
nv04_fbcon_accel_init(struct fb_info *info)
{
	struct nouveau_fbdev *nfbdev = info->par;
	struct drm_device *dev = nfbdev->helper.dev;
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_channel *chan = drm->channel;
	struct nvif_device *device = &drm->client.device;
	int surface_fmt, pattern_fmt, rect_fmt;
	int ret;

	switch (info->var.bits_per_pixel) {
	case 8:
		surface_fmt = 1;
		pattern_fmt = 3;
		rect_fmt = 3;
		break;
	case 16:
		surface_fmt = 4;
		pattern_fmt = 1;
		rect_fmt = 1;
		break;
	case 32:
		switch (info->var.transp.length) {
		case 0: /* depth 24 */
		case 8: /* depth 32 */
			break;
		default:
			return -EINVAL;
		}

		surface_fmt = 6;
		pattern_fmt = 3;
		rect_fmt = 3;
		break;
	default:
		return -EINVAL;
	}

	ret = nvif_object_init(&chan->user, 0x0062,
			       device->info.family >= NV_DEVICE_INFO_V0_CELSIUS ?
			       0x0062 : 0x0042, NULL, 0, &nfbdev->surf2d);
	if (ret)
		return ret;

	ret = nvif_object_init(&chan->user, 0x0019, 0x0019, NULL, 0,
			       &nfbdev->clip);
	if (ret)
		return ret;

	ret = nvif_object_init(&chan->user, 0x0043, 0x0043, NULL, 0,
			       &nfbdev->rop);
	if (ret)
		return ret;

	ret = nvif_object_init(&chan->user, 0x0044, 0x0044, NULL, 0,
			       &nfbdev->patt);
	if (ret)
		return ret;

	ret = nvif_object_init(&chan->user, 0x004a, 0x004a, NULL, 0,
			       &nfbdev->gdi);
	if (ret)
		return ret;

	ret = nvif_object_init(&chan->user, 0x005f,
			       device->info.chipset >= 0x11 ? 0x009f : 0x005f,
			       NULL, 0, &nfbdev->blit);
	if (ret)
		return ret;

	if (RING_SPACE(chan, 49 + (device->info.chipset >= 0x11 ? 4 : 0))) {
		nouveau_fbcon_gpu_lockup(info);
		return 0;
	}

	BEGIN_NV04(chan, NvSubCtxSurf2D, 0x0000, 1);
	OUT_RING(chan, nfbdev->surf2d.handle);
	BEGIN_NV04(chan, NvSubCtxSurf2D, 0x0184, 2);
	OUT_RING(chan, chan->vram.handle);
	OUT_RING(chan, chan->vram.handle);
	BEGIN_NV04(chan, NvSubCtxSurf2D, 0x0300, 4);
	OUT_RING(chan, surface_fmt);
	OUT_RING(chan, info->fix.line_length | (info->fix.line_length << 16));
	OUT_RING(chan, info->fix.smem_start - dev->mode_config.fb_base);
	OUT_RING(chan, info->fix.smem_start - dev->mode_config.fb_base);

	BEGIN_NV04(chan, NvSubCtxSurf2D, 0x0000, 1);
	OUT_RING(chan, nfbdev->rop.handle);
	BEGIN_NV04(chan, NvSubCtxSurf2D, 0x0300, 1);
	OUT_RING(chan, 0x55);

	BEGIN_NV04(chan, NvSubCtxSurf2D, 0x0000, 1);
	OUT_RING(chan, nfbdev->patt.handle);
	BEGIN_NV04(chan, NvSubCtxSurf2D, 0x0300, 8);
	OUT_RING(chan, pattern_fmt);
#ifdef __BIG_ENDIAN
	OUT_RING(chan, 2);
#else
	OUT_RING(chan, 1);
#endif
	OUT_RING(chan, 0);
	OUT_RING(chan, 1);
	OUT_RING(chan, ~0);
	OUT_RING(chan, ~0);
	OUT_RING(chan, ~0);
	OUT_RING(chan, ~0);

	BEGIN_NV04(chan, NvSubCtxSurf2D, 0x0000, 1);
	OUT_RING(chan, nfbdev->clip.handle);
	BEGIN_NV04(chan, NvSubCtxSurf2D, 0x0300, 2);
	OUT_RING(chan, 0);
	OUT_RING(chan, (info->var.yres_virtual << 16) | info->var.xres_virtual);

	BEGIN_NV04(chan, NvSubImageBlit, 0x0000, 1);
	OUT_RING(chan, nfbdev->blit.handle);
	BEGIN_NV04(chan, NvSubImageBlit, 0x019c, 1);
	OUT_RING(chan, nfbdev->surf2d.handle);
	BEGIN_NV04(chan, NvSubImageBlit, 0x02fc, 1);
	OUT_RING(chan, 3);
	if (device->info.chipset >= 0x11 /*XXX: oclass == 0x009f*/) {
		BEGIN_NV04(chan, NvSubImageBlit, 0x0120, 3);
		OUT_RING(chan, 0);
		OUT_RING(chan, 1);
		OUT_RING(chan, 2);
	}

	BEGIN_NV04(chan, NvSubGdiRect, 0x0000, 1);
	OUT_RING(chan, nfbdev->gdi.handle);
	BEGIN_NV04(chan, NvSubGdiRect, 0x0198, 1);
	OUT_RING(chan, nfbdev->surf2d.handle);
	BEGIN_NV04(chan, NvSubGdiRect, 0x0188, 2);
	OUT_RING(chan, nfbdev->patt.handle);
	OUT_RING(chan, nfbdev->rop.handle);
	BEGIN_NV04(chan, NvSubGdiRect, 0x0304, 1);
	OUT_RING(chan, 1);
	BEGIN_NV04(chan, NvSubGdiRect, 0x0300, 1);
	OUT_RING(chan, rect_fmt);
	BEGIN_NV04(chan, NvSubGdiRect, 0x02fc, 1);
	OUT_RING(chan, 3);

	FIRE_RING(chan);

	return 0;
}