#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int max_width; int max_height; int /*<<< orphan*/  fb_base; scalar_t__ min_height; scalar_t__ min_width; void* funcs; } ;
struct TYPE_8__ {TYPE_1__ mode_config; } ;
struct qxl_device {TYPE_2__ ddev; int /*<<< orphan*/  vram_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_config_init (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_mode_create_suggested_offset_properties (TYPE_2__*) ; 
 int /*<<< orphan*/  qdev_crtc_init (TYPE_2__*,int) ; 
 int /*<<< orphan*/  qdev_output_init (TYPE_2__*,int) ; 
 int qxl_create_monitors_object (struct qxl_device*) ; 
 int /*<<< orphan*/  qxl_display_read_client_monitors_config (struct qxl_device*) ; 
 int /*<<< orphan*/  qxl_mode_create_hotplug_mode_update_property (struct qxl_device*) ; 
 int /*<<< orphan*/  qxl_mode_funcs ; 
 int qxl_num_crtc ; 

int qxl_modeset_init(struct qxl_device *qdev)
{
	int i;
	int ret;

	drm_mode_config_init(&qdev->ddev);

	ret = qxl_create_monitors_object(qdev);
	if (ret)
		return ret;

	qdev->ddev.mode_config.funcs = (void *)&qxl_mode_funcs;

	/* modes will be validated against the framebuffer size */
	qdev->ddev.mode_config.min_width = 0;
	qdev->ddev.mode_config.min_height = 0;
	qdev->ddev.mode_config.max_width = 8192;
	qdev->ddev.mode_config.max_height = 8192;

	qdev->ddev.mode_config.fb_base = qdev->vram_base;

	drm_mode_create_suggested_offset_properties(&qdev->ddev);
	qxl_mode_create_hotplug_mode_update_property(qdev);

	for (i = 0 ; i < qxl_num_crtc; ++i) {
		qdev_crtc_init(&qdev->ddev, i);
		qdev_output_init(&qdev->ddev, i);
	}

	qxl_display_read_client_monitors_config(qdev);

	drm_mode_config_reset(&qdev->ddev);
	return 0;
}