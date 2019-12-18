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
struct rproc_vdev {int /*<<< orphan*/  refcount; } ;
struct rproc {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct virtio_device* dev_to_virtio (struct device*) ; 
 int /*<<< orphan*/  kfree (struct virtio_device*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rproc_vdev_release ; 
 struct rproc* vdev_to_rproc (struct virtio_device*) ; 
 struct rproc_vdev* vdev_to_rvdev (struct virtio_device*) ; 

__attribute__((used)) static void rproc_virtio_dev_release(struct device *dev)
{
	struct virtio_device *vdev = dev_to_virtio(dev);
	struct rproc_vdev *rvdev = vdev_to_rvdev(vdev);
	struct rproc *rproc = vdev_to_rproc(vdev);

	kfree(vdev);

	kref_put(&rvdev->refcount, rproc_vdev_release);

	put_device(&rproc->dev);
}