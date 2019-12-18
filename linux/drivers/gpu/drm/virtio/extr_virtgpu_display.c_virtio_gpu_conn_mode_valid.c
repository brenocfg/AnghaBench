#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {TYPE_1__ r; } ;
struct virtio_gpu_output {TYPE_2__ info; } ;
struct drm_display_mode {int type; int hdisplay; int vdisplay; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,int) ; 
 int DRM_MODE_TYPE_PREFERRED ; 
 int MODE_BAD ; 
 int MODE_OK ; 
 int XRES_DEF ; 
 int YRES_DEF ; 
 struct virtio_gpu_output* drm_connector_to_virtio_gpu_output (struct drm_connector*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum drm_mode_status virtio_gpu_conn_mode_valid(struct drm_connector *connector,
				      struct drm_display_mode *mode)
{
	struct virtio_gpu_output *output =
		drm_connector_to_virtio_gpu_output(connector);
	int width, height;

	width  = le32_to_cpu(output->info.r.width);
	height = le32_to_cpu(output->info.r.height);

	if (!(mode->type & DRM_MODE_TYPE_PREFERRED))
		return MODE_OK;
	if (mode->hdisplay == XRES_DEF && mode->vdisplay == YRES_DEF)
		return MODE_OK;
	if (mode->hdisplay <= width  && mode->hdisplay >= width - 16 &&
	    mode->vdisplay <= height && mode->vdisplay >= height - 16)
		return MODE_OK;

	DRM_DEBUG("del mode: %dx%d\n", mode->hdisplay, mode->vdisplay);
	return MODE_BAD;
}