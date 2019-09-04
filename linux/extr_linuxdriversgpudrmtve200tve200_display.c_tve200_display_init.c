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
typedef  int /*<<< orphan*/  u32 ;
struct tve200_drm_dev_private {int /*<<< orphan*/  connector; int /*<<< orphan*/  pipe; } ;
struct drm_device {struct tve200_drm_dev_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
#define  DRM_FORMAT_BGR565 138 
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
 int drm_simple_display_pipe_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tve200_display_funcs ; 

int tve200_display_init(struct drm_device *drm)
{
	struct tve200_drm_dev_private *priv = drm->dev_private;
	int ret;
	static const u32 formats[] = {
		DRM_FORMAT_XRGB8888,
		DRM_FORMAT_XBGR8888,
		DRM_FORMAT_RGB565,
		DRM_FORMAT_BGR565,
		DRM_FORMAT_XRGB1555,
		DRM_FORMAT_XBGR1555,
		/*
		 * The controller actually supports any YCbCr ordering,
		 * for packed YCbCr. This just lists the orderings that
		 * DRM supports.
		 */
		DRM_FORMAT_YUYV,
		DRM_FORMAT_YVYU,
		DRM_FORMAT_UYVY,
		DRM_FORMAT_VYUY,
		/* This uses three planes */
		DRM_FORMAT_YUV420,
	};

	ret = drm_simple_display_pipe_init(drm, &priv->pipe,
					   &tve200_display_funcs,
					   formats, ARRAY_SIZE(formats),
					   NULL,
					   priv->connector);
	if (ret)
		return ret;

	return 0;
}