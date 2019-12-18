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
 int /*<<< orphan*/  VIRTIO_F_RING_PACKED ; 
 int /*<<< orphan*/  __virtio_clear_bit (struct virtio_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rproc_transport_features(struct virtio_device *vdev)
{
	/*
	 * Packed ring isn't enabled on remoteproc for now,
	 * because remoteproc uses vring_new_virtqueue() which
	 * creates virtio rings on preallocated memory.
	 */
	__virtio_clear_bit(vdev, VIRTIO_F_RING_PACKED);
}