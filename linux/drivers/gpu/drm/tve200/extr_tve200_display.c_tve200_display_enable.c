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
struct tve200_drm_dev_private {scalar_t__ regs; int /*<<< orphan*/  clk; struct drm_connector* connector; } ;
struct drm_plane {TYPE_1__* state; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct drm_simple_display_pipe {struct drm_plane plane; struct drm_crtc crtc; } ;
struct drm_plane_state {int dummy; } ;
struct drm_framebuffer {TYPE_3__* format; } ;
struct drm_display_mode {int hdisplay; int vdisplay; } ;
struct drm_device {int /*<<< orphan*/  dev; struct tve200_drm_dev_private* dev_private; } ;
struct drm_crtc_state {struct drm_display_mode mode; } ;
struct TYPE_5__ {int bus_flags; } ;
struct drm_connector {TYPE_2__ display_info; } ;
struct TYPE_6__ {int format; } ;
struct TYPE_4__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE ; 
#define  DRM_FORMAT_BGR565 138 
 int DRM_FORMAT_BIG_ENDIAN ; 
#define  DRM_FORMAT_RGB565 137 
#define  DRM_FORMAT_UYVY 136 
#define  DRM_FORMAT_VYUY 135 
#define  DRM_FORMAT_XBGR1555 134 
#define  DRM_FORMAT_XBGR8888 133 
#define  DRM_FORMAT_XRGB1555 132 
#define  DRM_FORMAT_XRGB8888 131 
#define  DRM_FORMAT_YUV420 130 
#define  DRM_FORMAT_YUYV 129 
#define  DRM_FORMAT_YVYU 128 
 int TVE200_BGR ; 
 scalar_t__ TVE200_CTRL ; 
 int TVE200_CTRL_BBBP ; 
 int TVE200_CTRL_BURST_32_WORDS ; 
 int TVE200_CTRL_CSMODE ; 
 int TVE200_CTRL_IPRESOL_CIF ; 
 int TVE200_CTRL_IPRESOL_D1 ; 
 int TVE200_CTRL_IPRESOL_VGA ; 
 int TVE200_CTRL_NONINTERLACE ; 
 int TVE200_CTRL_NTSC ; 
 int TVE200_CTRL_RETRYCNT_16 ; 
 int TVE200_CTRL_TVCLKP ; 
 int TVE200_CTRL_YCBCRODR_CB0Y1CR0Y0 ; 
 int TVE200_CTRL_YCBCRODR_CR0Y1CB0Y0 ; 
 int TVE200_CTRL_YCBCRODR_Y1CB0Y0CR0 ; 
 int TVE200_CTRL_YCBCRODR_Y1CR0Y0CB0 ; 
 int TVE200_CTRL_YUV420 ; 
 int TVE200_IPDMOD_RGB555 ; 
 int TVE200_IPDMOD_RGB565 ; 
 int TVE200_IPDMOD_RGB888 ; 
 int TVE200_IPDMOD_YUV420 ; 
 int TVE200_IPDMOD_YUV422 ; 
 int TVE200_TVEEN ; 
 int TVE200_VSTSTYPE_VSYNC ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void tve200_display_enable(struct drm_simple_display_pipe *pipe,
				 struct drm_crtc_state *cstate,
				 struct drm_plane_state *plane_state)
{
	struct drm_crtc *crtc = &pipe->crtc;
	struct drm_plane *plane = &pipe->plane;
	struct drm_device *drm = crtc->dev;
	struct tve200_drm_dev_private *priv = drm->dev_private;
	const struct drm_display_mode *mode = &cstate->mode;
	struct drm_framebuffer *fb = plane->state->fb;
	struct drm_connector *connector = priv->connector;
	u32 format = fb->format->format;
	u32 ctrl1 = 0;

	clk_prepare_enable(priv->clk);

	/* Function 1 */
	ctrl1 |= TVE200_CTRL_CSMODE;
	/* Interlace mode for CCIR656: parameterize? */
	ctrl1 |= TVE200_CTRL_NONINTERLACE;
	/* 32 words per burst */
	ctrl1 |= TVE200_CTRL_BURST_32_WORDS;
	/* 16 retries */
	ctrl1 |= TVE200_CTRL_RETRYCNT_16;
	/* NTSC mode: parametrize? */
	ctrl1 |= TVE200_CTRL_NTSC;

	/* Vsync IRQ at start of Vsync at first */
	ctrl1 |= TVE200_VSTSTYPE_VSYNC;

	if (connector->display_info.bus_flags &
	    DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE)
		ctrl1 |= TVE200_CTRL_TVCLKP;

	if ((mode->hdisplay == 352 && mode->vdisplay == 240) || /* SIF(525) */
	    (mode->hdisplay == 352 && mode->vdisplay == 288)) { /* CIF(625) */
		ctrl1 |= TVE200_CTRL_IPRESOL_CIF;
		dev_info(drm->dev, "CIF mode\n");
	} else if (mode->hdisplay == 640 && mode->vdisplay == 480) {
		ctrl1 |= TVE200_CTRL_IPRESOL_VGA;
		dev_info(drm->dev, "VGA mode\n");
	} else if ((mode->hdisplay == 720 && mode->vdisplay == 480) ||
		   (mode->hdisplay == 720 && mode->vdisplay == 576)) {
		ctrl1 |= TVE200_CTRL_IPRESOL_D1;
		dev_info(drm->dev, "D1 mode\n");
	}

	if (format & DRM_FORMAT_BIG_ENDIAN) {
		ctrl1 |= TVE200_CTRL_BBBP;
		format &= ~DRM_FORMAT_BIG_ENDIAN;
	}

	switch (format) {
	case DRM_FORMAT_XRGB8888:
		ctrl1 |= TVE200_IPDMOD_RGB888;
		break;
	case DRM_FORMAT_RGB565:
		ctrl1 |= TVE200_IPDMOD_RGB565;
		break;
	case DRM_FORMAT_XRGB1555:
		ctrl1 |= TVE200_IPDMOD_RGB555;
		break;
	case DRM_FORMAT_XBGR8888:
		ctrl1 |= TVE200_IPDMOD_RGB888 | TVE200_BGR;
		break;
	case DRM_FORMAT_BGR565:
		ctrl1 |= TVE200_IPDMOD_RGB565 | TVE200_BGR;
		break;
	case DRM_FORMAT_XBGR1555:
		ctrl1 |= TVE200_IPDMOD_RGB555 | TVE200_BGR;
		break;
	case DRM_FORMAT_YUYV:
		ctrl1 |= TVE200_IPDMOD_YUV422;
		ctrl1 |= TVE200_CTRL_YCBCRODR_CR0Y1CB0Y0;
		break;
	case DRM_FORMAT_YVYU:
		ctrl1 |= TVE200_IPDMOD_YUV422;
		ctrl1 |= TVE200_CTRL_YCBCRODR_CB0Y1CR0Y0;
		break;
	case DRM_FORMAT_UYVY:
		ctrl1 |= TVE200_IPDMOD_YUV422;
		ctrl1 |= TVE200_CTRL_YCBCRODR_Y1CR0Y0CB0;
		break;
	case DRM_FORMAT_VYUY:
		ctrl1 |= TVE200_IPDMOD_YUV422;
		ctrl1 |= TVE200_CTRL_YCBCRODR_Y1CB0Y0CR0;
		break;
	case DRM_FORMAT_YUV420:
		ctrl1 |= TVE200_CTRL_YUV420;
		ctrl1 |= TVE200_IPDMOD_YUV420;
		break;
	default:
		dev_err(drm->dev, "Unknown FB format 0x%08x\n",
			fb->format->format);
		break;
	}

	ctrl1 |= TVE200_TVEEN;

	/* Turn it on */
	writel(ctrl1, priv->regs + TVE200_CTRL);

	drm_crtc_vblank_on(crtc);
}