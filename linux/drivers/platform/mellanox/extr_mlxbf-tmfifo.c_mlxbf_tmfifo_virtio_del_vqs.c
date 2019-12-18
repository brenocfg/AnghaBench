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
struct virtqueue {int dummy; } ;
struct virtio_device {int dummy; } ;
struct mlxbf_tmfifo_vring {struct virtqueue* vq; scalar_t__ desc; } ;
struct mlxbf_tmfifo_vdev {struct mlxbf_tmfifo_vring* vrings; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mlxbf_tmfifo_vring*) ; 
 int /*<<< orphan*/  mlxbf_tmfifo_release_pending_pkt (struct mlxbf_tmfifo_vring*) ; 
 struct mlxbf_tmfifo_vdev* mlxbf_vdev_to_tmfifo (struct virtio_device*) ; 
 int /*<<< orphan*/  vring_del_virtqueue (struct virtqueue*) ; 

__attribute__((used)) static void mlxbf_tmfifo_virtio_del_vqs(struct virtio_device *vdev)
{
	struct mlxbf_tmfifo_vdev *tm_vdev = mlxbf_vdev_to_tmfifo(vdev);
	struct mlxbf_tmfifo_vring *vring;
	struct virtqueue *vq;
	int i;

	for (i = 0; i < ARRAY_SIZE(tm_vdev->vrings); i++) {
		vring = &tm_vdev->vrings[i];

		/* Release the pending packet. */
		if (vring->desc)
			mlxbf_tmfifo_release_pending_pkt(vring);
		vq = vring->vq;
		if (vq) {
			vring->vq = NULL;
			vring_del_virtqueue(vq);
		}
	}
}