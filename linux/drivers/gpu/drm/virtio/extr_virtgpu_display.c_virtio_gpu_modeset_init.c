#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct virtio_gpu_device {int num_scanouts; TYPE_2__* ddev; } ;
struct TYPE_4__ {int quirk_addfb_prefer_host_byte_order; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_height; int /*<<< orphan*/  min_width; int /*<<< orphan*/ * helper_private; int /*<<< orphan*/ * funcs; } ;
struct TYPE_5__ {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  XRES_MAX ; 
 int /*<<< orphan*/  XRES_MIN ; 
 int /*<<< orphan*/  YRES_MAX ; 
 int /*<<< orphan*/  YRES_MIN ; 
 int /*<<< orphan*/  drm_mode_config_init (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  vgdev_output_init (struct virtio_gpu_device*,int) ; 
 int /*<<< orphan*/  virtio_gpu_mode_funcs ; 
 int /*<<< orphan*/  virtio_mode_config_helpers ; 

void virtio_gpu_modeset_init(struct virtio_gpu_device *vgdev)
{
	int i;

	drm_mode_config_init(vgdev->ddev);
	vgdev->ddev->mode_config.quirk_addfb_prefer_host_byte_order = true;
	vgdev->ddev->mode_config.funcs = &virtio_gpu_mode_funcs;
	vgdev->ddev->mode_config.helper_private = &virtio_mode_config_helpers;

	/* modes will be validated against the framebuffer size */
	vgdev->ddev->mode_config.min_width = XRES_MIN;
	vgdev->ddev->mode_config.min_height = YRES_MIN;
	vgdev->ddev->mode_config.max_width = XRES_MAX;
	vgdev->ddev->mode_config.max_height = YRES_MAX;

	for (i = 0 ; i < vgdev->num_scanouts; ++i)
		vgdev_output_init(vgdev, i);

	drm_mode_config_reset(vgdev->ddev);
}