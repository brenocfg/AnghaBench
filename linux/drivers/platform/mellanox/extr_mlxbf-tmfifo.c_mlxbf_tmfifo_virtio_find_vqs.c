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
struct virtqueue {struct mlxbf_tmfifo_vring* priv; } ;
struct virtio_device {int /*<<< orphan*/  dev; } ;
struct mlxbf_tmfifo_vring {struct virtqueue* vq; int /*<<< orphan*/  va; int /*<<< orphan*/  align; int /*<<< orphan*/  num; } ;
struct mlxbf_tmfifo_vdev {struct mlxbf_tmfifo_vring* vrings; } ;
struct irq_affinity {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct mlxbf_tmfifo_vring*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxbf_tmfifo_virtio_del_vqs (struct virtio_device*) ; 
 int /*<<< orphan*/  mlxbf_tmfifo_virtio_notify ; 
 struct mlxbf_tmfifo_vdev* mlxbf_vdev_to_tmfifo (struct virtio_device*) ; 
 struct virtqueue* vring_new_virtqueue (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct virtio_device*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const* const) ; 
 int vring_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxbf_tmfifo_virtio_find_vqs(struct virtio_device *vdev,
					unsigned int nvqs,
					struct virtqueue *vqs[],
					vq_callback_t *callbacks[],
					const char * const names[],
					const bool *ctx,
					struct irq_affinity *desc)
{
	struct mlxbf_tmfifo_vdev *tm_vdev = mlxbf_vdev_to_tmfifo(vdev);
	struct mlxbf_tmfifo_vring *vring;
	struct virtqueue *vq;
	int i, ret, size;

	if (nvqs > ARRAY_SIZE(tm_vdev->vrings))
		return -EINVAL;

	for (i = 0; i < nvqs; ++i) {
		if (!names[i]) {
			ret = -EINVAL;
			goto error;
		}
		vring = &tm_vdev->vrings[i];

		/* zero vring */
		size = vring_size(vring->num, vring->align);
		memset(vring->va, 0, size);
		vq = vring_new_virtqueue(i, vring->num, vring->align, vdev,
					 false, false, vring->va,
					 mlxbf_tmfifo_virtio_notify,
					 callbacks[i], names[i]);
		if (!vq) {
			dev_err(&vdev->dev, "vring_new_virtqueue failed\n");
			ret = -ENOMEM;
			goto error;
		}

		vqs[i] = vq;
		vring->vq = vq;
		vq->priv = vring;
	}

	return 0;

error:
	mlxbf_tmfifo_virtio_del_vqs(vdev);
	return ret;
}