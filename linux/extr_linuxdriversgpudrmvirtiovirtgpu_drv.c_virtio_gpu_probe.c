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
struct virtio_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  driver ; 
 int drm_virtio_init (int /*<<< orphan*/ *,struct virtio_device*) ; 
 scalar_t__ vgacon_text_force () ; 
 int virtio_gpu_modeset ; 

__attribute__((used)) static int virtio_gpu_probe(struct virtio_device *vdev)
{
	if (vgacon_text_force() && virtio_gpu_modeset == -1)
		return -EINVAL;

	if (virtio_gpu_modeset == 0)
		return -EINVAL;

	return drm_virtio_init(&driver, vdev);
}