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
struct virtnet_info {struct virtio_device* vdev; } ;
struct virtio_device {TYPE_1__* config; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* del_vqs ) (struct virtio_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct virtio_device*) ; 
 int /*<<< orphan*/  virtnet_clean_affinity (struct virtnet_info*) ; 
 int /*<<< orphan*/  virtnet_free_queues (struct virtnet_info*) ; 

__attribute__((used)) static void virtnet_del_vqs(struct virtnet_info *vi)
{
	struct virtio_device *vdev = vi->vdev;

	virtnet_clean_affinity(vi);

	vdev->config->del_vqs(vdev);

	virtnet_free_queues(vi);
}