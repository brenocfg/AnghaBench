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
struct qxl_output {int index; } ;
struct qxl_head {unsigned int width; unsigned int height; } ;
struct qxl_device {unsigned int monitors_config_width; unsigned int monitors_config_height; TYPE_2__* client_monitors_config; TYPE_1__* monitors_config; } ;
struct drm_display_mode {unsigned int hdisplay; unsigned int vdisplay; int /*<<< orphan*/  type; } ;
struct drm_device {struct qxl_device* dev_private; } ;
struct drm_connector {struct drm_device* dev; } ;
struct TYPE_4__ {int count; struct qxl_head* heads; } ;
struct TYPE_3__ {int max_allowed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  DRM_MODE_TYPE_PREFERRED ; 
 struct qxl_output* drm_connector_to_qxl_output (struct drm_connector*) ; 
 struct drm_display_mode* drm_cvt_mode (struct drm_device*,unsigned int,unsigned int,int,int,int,int) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 

__attribute__((used)) static int qxl_add_monitors_config_modes(struct drm_connector *connector,
                                         unsigned *pwidth,
                                         unsigned *pheight)
{
	struct drm_device *dev = connector->dev;
	struct qxl_device *qdev = dev->dev_private;
	struct qxl_output *output = drm_connector_to_qxl_output(connector);
	int h = output->index;
	struct drm_display_mode *mode = NULL;
	struct qxl_head *head;

	if (!qdev->monitors_config)
		return 0;
	if (h >= qdev->monitors_config->max_allowed)
		return 0;
	if (!qdev->client_monitors_config)
		return 0;
	if (h >= qdev->client_monitors_config->count)
		return 0;

	head = &qdev->client_monitors_config->heads[h];
	DRM_DEBUG_KMS("head %d is %dx%d\n", h, head->width, head->height);

	mode = drm_cvt_mode(dev, head->width, head->height, 60, false, false,
			    false);
	mode->type |= DRM_MODE_TYPE_PREFERRED;
	mode->hdisplay = head->width;
	mode->vdisplay = head->height;
	drm_mode_set_name(mode);
	*pwidth = head->width;
	*pheight = head->height;
	drm_mode_probed_add(connector, mode);
	/* remember the last custom size for mode validation */
	qdev->monitors_config_width = mode->hdisplay;
	qdev->monitors_config_height = mode->vdisplay;
	return 1;
}