#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_crtc {TYPE_5__* primary; struct drm_device* dev; } ;
struct TYPE_6__ {struct drm_crtc crtc; } ;
struct aspeed_gfx {scalar_t__ base; TYPE_1__ pipe; } ;
struct TYPE_10__ {TYPE_4__* state; } ;
struct TYPE_9__ {TYPE_3__* fb; } ;
struct TYPE_8__ {TYPE_2__* format; } ;
struct TYPE_7__ {int format; } ;

/* Variables and functions */
 scalar_t__ CRT_CTRL1 ; 
 int CRT_CTRL_COLOR_MASK ; 
 int CRT_CTRL_COLOR_RGB565 ; 
 int CRT_CTRL_COLOR_XRGB8888 ; 
#define  DRM_FORMAT_RGB565 129 
#define  DRM_FORMAT_XRGB8888 128 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int const) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int aspeed_gfx_set_pixel_fmt(struct aspeed_gfx *priv, u32 *bpp)
{
	struct drm_crtc *crtc = &priv->pipe.crtc;
	struct drm_device *drm = crtc->dev;
	const u32 format = crtc->primary->state->fb->format->format;
	u32 ctrl1;

	ctrl1 = readl(priv->base + CRT_CTRL1);
	ctrl1 &= ~CRT_CTRL_COLOR_MASK;

	switch (format) {
	case DRM_FORMAT_RGB565:
		dev_dbg(drm->dev, "Setting up RGB565 mode\n");
		ctrl1 |= CRT_CTRL_COLOR_RGB565;
		*bpp = 16;
		break;
	case DRM_FORMAT_XRGB8888:
		dev_dbg(drm->dev, "Setting up XRGB8888 mode\n");
		ctrl1 |= CRT_CTRL_COLOR_XRGB8888;
		*bpp = 32;
		break;
	default:
		dev_err(drm->dev, "Unhandled pixel format %08x\n", format);
		return -EINVAL;
	}

	writel(ctrl1, priv->base + CRT_CTRL1);

	return 0;
}