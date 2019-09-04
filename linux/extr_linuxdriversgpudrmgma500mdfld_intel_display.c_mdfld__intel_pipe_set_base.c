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
typedef  unsigned long u32 ;
struct psb_offset {int /*<<< orphan*/  surf; int /*<<< orphan*/  linoff; int /*<<< orphan*/  cntr; int /*<<< orphan*/  stride; } ;
struct gma_crtc {int pipe; } ;
struct drm_psb_private {struct psb_offset* regmap; } ;
struct drm_framebuffer {int* pitches; TYPE_2__* format; int /*<<< orphan*/ * obj; } ;
struct drm_device {int /*<<< orphan*/  dev; struct drm_psb_private* dev_private; } ;
struct drm_crtc {TYPE_1__* primary; struct drm_device* dev; } ;
struct TYPE_6__ {unsigned long offset; } ;
struct TYPE_5__ {int* cpp; int depth; } ;
struct TYPE_4__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 unsigned long DISPPLANE_15_16BPP ; 
 unsigned long DISPPLANE_16BPP ; 
 unsigned long DISPPLANE_32BPP_NO_ALPHA ; 
 unsigned long DISPPLANE_8BPP ; 
 unsigned long DISPPLANE_PIXFORMAT_MASK ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 unsigned long REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,unsigned long) ; 
 int check_fb (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  globle_dev ; 
 int /*<<< orphan*/  gma_power_begin (struct drm_device*,int) ; 
 int /*<<< orphan*/  gma_power_end (struct drm_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct drm_device*,int) ; 
 struct gma_crtc* to_gma_crtc (struct drm_crtc*) ; 
 TYPE_3__* to_gtt_range (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdfld__intel_pipe_set_base(struct drm_crtc *crtc, int x, int y,
				struct drm_framebuffer *old_fb)
{
	struct drm_device *dev = crtc->dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct drm_framebuffer *fb = crtc->primary->fb;
	struct gma_crtc *gma_crtc = to_gma_crtc(crtc);
	int pipe = gma_crtc->pipe;
	const struct psb_offset *map = &dev_priv->regmap[pipe];
	unsigned long start, offset;
	u32 dspcntr;
	int ret;

	memcpy(&globle_dev, dev, sizeof(struct drm_device));

	dev_dbg(dev->dev, "pipe = 0x%x.\n", pipe);

	/* no fb bound */
	if (!fb) {
		dev_dbg(dev->dev, "No FB bound\n");
		return 0;
	}

	ret = check_fb(fb);
	if (ret)
		return ret;

	if (pipe > 2) {
		DRM_ERROR("Illegal Pipe Number.\n");
		return -EINVAL;
	}

	if (!gma_power_begin(dev, true))
		return 0;

	start = to_gtt_range(fb->obj[0])->offset;
	offset = y * fb->pitches[0] + x * fb->format->cpp[0];

	REG_WRITE(map->stride, fb->pitches[0]);
	dspcntr = REG_READ(map->cntr);
	dspcntr &= ~DISPPLANE_PIXFORMAT_MASK;

	switch (fb->format->cpp[0] * 8) {
	case 8:
		dspcntr |= DISPPLANE_8BPP;
		break;
	case 16:
		if (fb->format->depth == 15)
			dspcntr |= DISPPLANE_15_16BPP;
		else
			dspcntr |= DISPPLANE_16BPP;
		break;
	case 24:
	case 32:
		dspcntr |= DISPPLANE_32BPP_NO_ALPHA;
		break;
	}
	REG_WRITE(map->cntr, dspcntr);

	dev_dbg(dev->dev, "Writing base %08lX %08lX %d %d\n",
						start, offset, x, y);
	REG_WRITE(map->linoff, offset);
	REG_READ(map->linoff);
	REG_WRITE(map->surf, start);
	REG_READ(map->surf);

	gma_power_end(dev);

	return 0;
}