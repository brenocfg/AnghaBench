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
typedef  scalar_t__ u32 ;
struct virtio_device {scalar_t__ features; } ;
struct rproc_vdev {int rsc_offset; TYPE_1__* rproc; } ;
struct fw_rsc_vdev {scalar_t__ gfeatures; } ;
struct TYPE_2__ {scalar_t__ table_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  rproc_transport_features (struct virtio_device*) ; 
 struct rproc_vdev* vdev_to_rvdev (struct virtio_device*) ; 
 int /*<<< orphan*/  vring_transport_features (struct virtio_device*) ; 

__attribute__((used)) static int rproc_virtio_finalize_features(struct virtio_device *vdev)
{
	struct rproc_vdev *rvdev = vdev_to_rvdev(vdev);
	struct fw_rsc_vdev *rsc;

	rsc = (void *)rvdev->rproc->table_ptr + rvdev->rsc_offset;

	/* Give virtio_ring a chance to accept features */
	vring_transport_features(vdev);

	/* Give virtio_rproc a chance to accept features. */
	rproc_transport_features(vdev);

	/* Make sure we don't have any features > 32 bits! */
	BUG_ON((u32)vdev->features != vdev->features);

	/*
	 * Remember the finalized features of our vdev, and provide it
	 * to the remote processor once it is powered on.
	 */
	rsc->gfeatures = vdev->features;

	return 0;
}