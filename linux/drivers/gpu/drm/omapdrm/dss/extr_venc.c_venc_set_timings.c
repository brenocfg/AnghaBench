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
struct venc_device {int /*<<< orphan*/  venc_lock; TYPE_1__* dss; int /*<<< orphan*/ * config; } ;
struct omap_dss_device {int dummy; } ;
struct drm_display_mode {int dummy; } ;
typedef  enum venc_videomode { ____Placeholder_venc_videomode } venc_videomode ;
struct TYPE_2__ {int /*<<< orphan*/  dispc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
#define  VENC_MODE_NTSC 129 
#define  VENC_MODE_PAL 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dispc_set_tv_pclk (int /*<<< orphan*/ ,int) ; 
 struct venc_device* dssdev_to_venc (struct omap_dss_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  venc_config_ntsc_trm ; 
 int /*<<< orphan*/  venc_config_pal_trm ; 
 int venc_get_videomode (struct drm_display_mode const*) ; 

__attribute__((used)) static void venc_set_timings(struct omap_dss_device *dssdev,
			     const struct drm_display_mode *mode)
{
	struct venc_device *venc = dssdev_to_venc(dssdev);
	enum venc_videomode venc_mode = venc_get_videomode(mode);

	DSSDBG("venc_set_timings\n");

	mutex_lock(&venc->venc_lock);

	switch (venc_mode) {
	default:
		WARN_ON_ONCE(1);
		/* Fall-through */
	case VENC_MODE_PAL:
		venc->config = &venc_config_pal_trm;
		break;

	case VENC_MODE_NTSC:
		venc->config = &venc_config_ntsc_trm;
		break;
	}

	dispc_set_tv_pclk(venc->dss->dispc, 13500000);

	mutex_unlock(&venc->venc_lock);
}