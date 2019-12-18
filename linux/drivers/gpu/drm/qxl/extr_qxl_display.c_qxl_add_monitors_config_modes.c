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
struct qxl_output {int index; } ;
struct qxl_head {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct qxl_device {TYPE_1__* client_monitors_config; int /*<<< orphan*/  monitors_config; } ;
struct drm_device {struct qxl_device* dev_private; } ;
struct drm_connector {struct drm_device* dev; } ;
struct TYPE_2__ {int count; struct qxl_head* heads; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qxl_output* drm_connector_to_qxl_output (struct drm_connector*) ; 
 int qxl_add_mode (struct drm_connector*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qxl_num_crtc ; 

__attribute__((used)) static int qxl_add_monitors_config_modes(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct qxl_device *qdev = dev->dev_private;
	struct qxl_output *output = drm_connector_to_qxl_output(connector);
	int h = output->index;
	struct qxl_head *head;

	if (!qdev->monitors_config)
		return 0;
	if (h >= qxl_num_crtc)
		return 0;
	if (!qdev->client_monitors_config)
		return 0;
	if (h >= qdev->client_monitors_config->count)
		return 0;

	head = &qdev->client_monitors_config->heads[h];
	DRM_DEBUG_KMS("head %d is %dx%d\n", h, head->width, head->height);

	return qxl_add_mode(connector, head->width, head->height, true);
}