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
typedef  int u32 ;
struct TYPE_4__ {int* bus_formats; scalar_t__ num_bus_formats; } ;
struct TYPE_5__ {TYPE_1__ display_info; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_6__ {struct drm_crtc crtc; } ;
struct mxsfb_drm_private {scalar_t__ base; TYPE_2__ connector; TYPE_3__ pipe; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CTRL_BUS_WIDTH_MASK ; 
 int CTRL_SET_BUS_WIDTH (int /*<<< orphan*/ ) ; 
 scalar_t__ LCDC_CTRL ; 
#define  MEDIA_BUS_FMT_RGB565_1X16 130 
#define  MEDIA_BUS_FMT_RGB666_1X18 129 
#define  MEDIA_BUS_FMT_RGB888_1X24 128 
 int /*<<< orphan*/  STMLCDIF_16BIT ; 
 int /*<<< orphan*/  STMLCDIF_18BIT ; 
 int /*<<< orphan*/  STMLCDIF_24BIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mxsfb_set_bus_fmt(struct mxsfb_drm_private *mxsfb)
{
	struct drm_crtc *crtc = &mxsfb->pipe.crtc;
	struct drm_device *drm = crtc->dev;
	u32 bus_format = MEDIA_BUS_FMT_RGB888_1X24;
	u32 reg;

	reg = readl(mxsfb->base + LCDC_CTRL);

	if (mxsfb->connector.display_info.num_bus_formats)
		bus_format = mxsfb->connector.display_info.bus_formats[0];

	reg &= ~CTRL_BUS_WIDTH_MASK;
	switch (bus_format) {
	case MEDIA_BUS_FMT_RGB565_1X16:
		reg |= CTRL_SET_BUS_WIDTH(STMLCDIF_16BIT);
		break;
	case MEDIA_BUS_FMT_RGB666_1X18:
		reg |= CTRL_SET_BUS_WIDTH(STMLCDIF_18BIT);
		break;
	case MEDIA_BUS_FMT_RGB888_1X24:
		reg |= CTRL_SET_BUS_WIDTH(STMLCDIF_24BIT);
		break;
	default:
		dev_err(drm->dev, "Unknown media bus format %d\n", bus_format);
		break;
	}
	writel(reg, mxsfb->base + LCDC_CTRL);
}