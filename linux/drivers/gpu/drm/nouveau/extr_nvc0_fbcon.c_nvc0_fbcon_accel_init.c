#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nouveau_framebuffer {TYPE_5__* vma; } ;
struct TYPE_12__ {int handle; } ;
struct TYPE_7__ {int /*<<< orphan*/  fb; struct drm_device* dev; } ;
struct nouveau_fbdev {TYPE_6__ twod; TYPE_1__ helper; } ;
struct nouveau_drm {struct nouveau_channel* channel; } ;
struct nouveau_channel {int /*<<< orphan*/  user; } ;
struct TYPE_8__ {int /*<<< orphan*/  length; } ;
struct TYPE_10__ {int bits_per_pixel; int xres_virtual; int yres_virtual; TYPE_2__ transp; } ;
struct TYPE_9__ {int line_length; } ;
struct fb_info {TYPE_4__ var; TYPE_3__ fix; struct nouveau_fbdev* par; } ;
struct drm_device {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_NVC0 (struct nouveau_channel*,int /*<<< orphan*/ ,int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FIRE_RING (struct nouveau_channel*) ; 
 int /*<<< orphan*/  NvSub2D ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_fbcon_gpu_lockup (struct fb_info*) ; 
 struct nouveau_framebuffer* nouveau_framebuffer (int /*<<< orphan*/ ) ; 
 int nvif_object_init (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

int
nvc0_fbcon_accel_init(struct fb_info *info)
{
	struct nouveau_fbdev *nfbdev = info->par;
	struct drm_device *dev = nfbdev->helper.dev;
	struct nouveau_framebuffer *fb = nouveau_framebuffer(nfbdev->helper.fb);
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nouveau_channel *chan = drm->channel;
	int ret, format;

	ret = nvif_object_init(&chan->user, 0x902d, 0x902d, NULL, 0,
			       &nfbdev->twod);
	if (ret)
		return ret;

	switch (info->var.bits_per_pixel) {
	case 8:
		format = 0xf3;
		break;
	case 15:
		format = 0xf8;
		break;
	case 16:
		format = 0xe8;
		break;
	case 32:
		switch (info->var.transp.length) {
		case 0: /* depth 24 */
		case 8: /* depth 32, just use 24.. */
			format = 0xe6;
			break;
		case 2: /* depth 30 */
			format = 0xd1;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	ret = RING_SPACE(chan, 58);
	if (ret) {
		WARN_ON(1);
		nouveau_fbcon_gpu_lockup(info);
		return ret;
	}

	BEGIN_NVC0(chan, NvSub2D, 0x0000, 1);
	OUT_RING  (chan, nfbdev->twod.handle);
	BEGIN_NVC0(chan, NvSub2D, 0x0290, 1);
	OUT_RING  (chan, 0);
	BEGIN_NVC0(chan, NvSub2D, 0x0888, 1);
	OUT_RING  (chan, 1);
	BEGIN_NVC0(chan, NvSub2D, 0x02ac, 1);
	OUT_RING  (chan, 3);
	BEGIN_NVC0(chan, NvSub2D, 0x02a0, 1);
	OUT_RING  (chan, 0x55);
	BEGIN_NVC0(chan, NvSub2D, 0x08c0, 4);
	OUT_RING  (chan, 0);
	OUT_RING  (chan, 1);
	OUT_RING  (chan, 0);
	OUT_RING  (chan, 1);
	BEGIN_NVC0(chan, NvSub2D, 0x0580, 2);
	OUT_RING  (chan, 4);
	OUT_RING  (chan, format);
	BEGIN_NVC0(chan, NvSub2D, 0x02e8, 2);
	OUT_RING  (chan, 2);
	OUT_RING  (chan, 1);

	BEGIN_NVC0(chan, NvSub2D, 0x0804, 1);
	OUT_RING  (chan, format);
	BEGIN_NVC0(chan, NvSub2D, 0x0800, 1);
	OUT_RING  (chan, 1);
	BEGIN_NVC0(chan, NvSub2D, 0x0808, 3);
	OUT_RING  (chan, 0);
	OUT_RING  (chan, 0);
	OUT_RING  (chan, 1);
	BEGIN_NVC0(chan, NvSub2D, 0x081c, 1);
	OUT_RING  (chan, 1);
	BEGIN_NVC0(chan, NvSub2D, 0x0840, 4);
	OUT_RING  (chan, 0);
	OUT_RING  (chan, 1);
	OUT_RING  (chan, 0);
	OUT_RING  (chan, 1);
	BEGIN_NVC0(chan, NvSub2D, 0x0200, 10);
	OUT_RING  (chan, format);
	OUT_RING  (chan, 1);
	OUT_RING  (chan, 0);
	OUT_RING  (chan, 1);
	OUT_RING  (chan, 0);
	OUT_RING  (chan, info->fix.line_length);
	OUT_RING  (chan, info->var.xres_virtual);
	OUT_RING  (chan, info->var.yres_virtual);
	OUT_RING  (chan, upper_32_bits(fb->vma->addr));
	OUT_RING  (chan, lower_32_bits(fb->vma->addr));
	BEGIN_NVC0(chan, NvSub2D, 0x0230, 10);
	OUT_RING  (chan, format);
	OUT_RING  (chan, 1);
	OUT_RING  (chan, 0);
	OUT_RING  (chan, 1);
	OUT_RING  (chan, 0);
	OUT_RING  (chan, info->fix.line_length);
	OUT_RING  (chan, info->var.xres_virtual);
	OUT_RING  (chan, info->var.yres_virtual);
	OUT_RING  (chan, upper_32_bits(fb->vma->addr));
	OUT_RING  (chan, lower_32_bits(fb->vma->addr));
	FIRE_RING (chan);

	return 0;
}