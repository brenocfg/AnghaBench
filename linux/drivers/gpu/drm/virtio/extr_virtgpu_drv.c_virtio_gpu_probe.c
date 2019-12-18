#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* parent; } ;
struct virtio_device {struct drm_device* priv; TYPE_3__ dev; } ;
struct drm_device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int /*<<< orphan*/  driver ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fbdev_generic_setup (struct drm_device*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ vgacon_text_force () ; 
 int virtio_gpu_init (struct drm_device*) ; 
 int virtio_gpu_modeset ; 
 int virtio_gpu_pci_quirk (struct drm_device*,struct virtio_device*) ; 

__attribute__((used)) static int virtio_gpu_probe(struct virtio_device *vdev)
{
	struct drm_device *dev;
	int ret;

	if (vgacon_text_force() && virtio_gpu_modeset == -1)
		return -EINVAL;

	if (virtio_gpu_modeset == 0)
		return -EINVAL;

	dev = drm_dev_alloc(&driver, &vdev->dev);
	if (IS_ERR(dev))
		return PTR_ERR(dev);
	vdev->priv = dev;

	if (!strcmp(vdev->dev.parent->bus->name, "pci")) {
		ret = virtio_gpu_pci_quirk(dev, vdev);
		if (ret)
			goto err_free;
	}

	ret = virtio_gpu_init(dev);
	if (ret)
		goto err_free;

	ret = drm_dev_register(dev, 0);
	if (ret)
		goto err_free;

	drm_fbdev_generic_setup(vdev->priv, 32);
	return 0;

err_free:
	drm_dev_put(dev);
	return ret;
}