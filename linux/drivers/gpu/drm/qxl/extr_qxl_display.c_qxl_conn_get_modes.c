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
struct qxl_output {size_t index; } ;
struct qxl_head {int width; int height; } ;
struct qxl_device {TYPE_1__* client_monitors_config; } ;
struct drm_device {struct qxl_device* dev_private; } ;
struct drm_connector {struct drm_device* dev; } ;
struct TYPE_2__ {struct qxl_head* heads; } ;

/* Variables and functions */
 scalar_t__ drm_add_modes_noedid (struct drm_connector*,int,int) ; 
 struct qxl_output* drm_connector_to_qxl_output (struct drm_connector*) ; 
 int /*<<< orphan*/  drm_set_preferred_mode (struct drm_connector*,unsigned int,unsigned int) ; 
 scalar_t__ qxl_add_extra_modes (struct drm_connector*) ; 
 scalar_t__ qxl_add_monitors_config_modes (struct drm_connector*) ; 

__attribute__((used)) static int qxl_conn_get_modes(struct drm_connector *connector)
{
	struct drm_device *dev = connector->dev;
	struct qxl_device *qdev = dev->dev_private;
	struct qxl_output *output = drm_connector_to_qxl_output(connector);
	unsigned int pwidth = 1024;
	unsigned int pheight = 768;
	int ret = 0;

	if (qdev->client_monitors_config) {
		struct qxl_head *head;
		head = &qdev->client_monitors_config->heads[output->index];
		if (head->width)
			pwidth = head->width;
		if (head->height)
			pheight = head->height;
	}

	ret += drm_add_modes_noedid(connector, 8192, 8192);
	ret += qxl_add_extra_modes(connector);
	ret += qxl_add_monitors_config_modes(connector);
	drm_set_preferred_mode(connector, pwidth, pheight);
	return ret;
}