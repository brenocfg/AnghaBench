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
struct virtio_device {TYPE_1__* config; int /*<<< orphan*/  dev; } ;
struct nvdimm_bus {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct virtio_device*) ;int /*<<< orphan*/  (* del_vqs ) (struct virtio_device*) ;} ;

/* Variables and functions */
 struct nvdimm_bus* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvdimm_bus_unregister (struct nvdimm_bus*) ; 
 int /*<<< orphan*/  stub1 (struct virtio_device*) ; 
 int /*<<< orphan*/  stub2 (struct virtio_device*) ; 

__attribute__((used)) static void virtio_pmem_remove(struct virtio_device *vdev)
{
	struct nvdimm_bus *nvdimm_bus = dev_get_drvdata(&vdev->dev);

	nvdimm_bus_unregister(nvdimm_bus);
	vdev->config->del_vqs(vdev);
	vdev->config->reset(vdev);
}