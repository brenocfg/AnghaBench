#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mcde {int /*<<< orphan*/  connector; int /*<<< orphan*/  pipe; scalar_t__ te_sync; } ;
struct drm_device {struct mcde* dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  disable_vblank; int /*<<< orphan*/  enable_vblank; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
#define  DRM_FORMAT_ABGR4444 142 
#define  DRM_FORMAT_ABGR8888 141 
#define  DRM_FORMAT_ARGB4444 140 
#define  DRM_FORMAT_ARGB8888 139 
#define  DRM_FORMAT_BGR565 138 
#define  DRM_FORMAT_BGR888 137 
#define  DRM_FORMAT_RGB565 136 
#define  DRM_FORMAT_RGB888 135 
#define  DRM_FORMAT_XBGR1555 134 
#define  DRM_FORMAT_XBGR4444 133 
#define  DRM_FORMAT_XBGR8888 132 
#define  DRM_FORMAT_XRGB1555 131 
#define  DRM_FORMAT_XRGB4444 130 
#define  DRM_FORMAT_XRGB8888 129 
#define  DRM_FORMAT_YUV422 128 
 int drm_simple_display_pipe_init (struct drm_device*,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcde_display_disable_vblank ; 
 int /*<<< orphan*/  mcde_display_enable_vblank ; 
 TYPE_1__ mcde_display_funcs ; 

int mcde_display_init(struct drm_device *drm)
{
	struct mcde *mcde = drm->dev_private;
	int ret;
	static const u32 formats[] = {
		DRM_FORMAT_ARGB8888,
		DRM_FORMAT_ABGR8888,
		DRM_FORMAT_XRGB8888,
		DRM_FORMAT_XBGR8888,
		DRM_FORMAT_RGB888,
		DRM_FORMAT_BGR888,
		DRM_FORMAT_ARGB4444,
		DRM_FORMAT_ABGR4444,
		DRM_FORMAT_XRGB4444,
		DRM_FORMAT_XBGR4444,
		/* These are actually IRGB1555 so intensity bit is lost */
		DRM_FORMAT_XRGB1555,
		DRM_FORMAT_XBGR1555,
		DRM_FORMAT_RGB565,
		DRM_FORMAT_BGR565,
		DRM_FORMAT_YUV422,
	};

	/* Provide vblank only when we have TE enabled */
	if (mcde->te_sync) {
		mcde_display_funcs.enable_vblank = mcde_display_enable_vblank;
		mcde_display_funcs.disable_vblank = mcde_display_disable_vblank;
	}

	ret = drm_simple_display_pipe_init(drm, &mcde->pipe,
					   &mcde_display_funcs,
					   formats, ARRAY_SIZE(formats),
					   NULL,
					   mcde->connector);
	if (ret)
		return ret;

	return 0;
}