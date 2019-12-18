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
struct virtio_device {struct drm_device* priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dev_unregister (struct drm_device*) ; 
 int /*<<< orphan*/  drm_put_dev (struct drm_device*) ; 
 int /*<<< orphan*/  virtio_gpu_deinit (struct drm_device*) ; 

__attribute__((used)) static void virtio_gpu_remove(struct virtio_device *vdev)
{
	struct drm_device *dev = vdev->priv;

	drm_dev_unregister(dev);
	virtio_gpu_deinit(dev);
	drm_put_dev(dev);
}