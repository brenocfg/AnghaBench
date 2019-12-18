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
struct virtio_gpu_device {int num_scanouts; int /*<<< orphan*/  ddev; TYPE_1__* outputs; } ;
struct TYPE_2__ {int /*<<< orphan*/  edid; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_helper_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void virtio_gpu_modeset_fini(struct virtio_gpu_device *vgdev)
{
	int i;

	for (i = 0 ; i < vgdev->num_scanouts; ++i)
		kfree(vgdev->outputs[i].edid);
	drm_atomic_helper_shutdown(vgdev->ddev);
	drm_mode_config_cleanup(vgdev->ddev);
}