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
typedef  int /*<<< orphan*/  vq_callback_t ;
struct virtio_device {int dummy; } ;
struct viommu_dev {int /*<<< orphan*/  vqs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIOMMU_NR_VQS ; 
 struct virtio_device* dev_to_virtio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * viommu_event_handler ; 
 int virtio_find_vqs (struct virtio_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int viommu_init_vqs(struct viommu_dev *viommu)
{
	struct virtio_device *vdev = dev_to_virtio(viommu->dev);
	const char *names[] = { "request", "event" };
	vq_callback_t *callbacks[] = {
		NULL, /* No async requests */
		viommu_event_handler,
	};

	return virtio_find_vqs(vdev, VIOMMU_NR_VQS, viommu->vqs, callbacks,
			       names, NULL);
}