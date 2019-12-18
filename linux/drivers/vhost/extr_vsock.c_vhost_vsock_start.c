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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct vhost_vsock {TYPE_1__ dev; struct vhost_virtqueue* vqs; } ;
struct vhost_virtqueue {int /*<<< orphan*/  mutex; struct vhost_vsock* private_data; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct vhost_virtqueue*) ; 
 int EFAULT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vhost_dev_check_owner (TYPE_1__*) ; 
 int /*<<< orphan*/  vhost_vq_access_ok (struct vhost_virtqueue*) ; 
 int vhost_vq_init_access (struct vhost_virtqueue*) ; 

__attribute__((used)) static int vhost_vsock_start(struct vhost_vsock *vsock)
{
	struct vhost_virtqueue *vq;
	size_t i;
	int ret;

	mutex_lock(&vsock->dev.mutex);

	ret = vhost_dev_check_owner(&vsock->dev);
	if (ret)
		goto err;

	for (i = 0; i < ARRAY_SIZE(vsock->vqs); i++) {
		vq = &vsock->vqs[i];

		mutex_lock(&vq->mutex);

		if (!vhost_vq_access_ok(vq)) {
			ret = -EFAULT;
			goto err_vq;
		}

		if (!vq->private_data) {
			vq->private_data = vsock;
			ret = vhost_vq_init_access(vq);
			if (ret)
				goto err_vq;
		}

		mutex_unlock(&vq->mutex);
	}

	mutex_unlock(&vsock->dev.mutex);
	return 0;

err_vq:
	vq->private_data = NULL;
	mutex_unlock(&vq->mutex);

	for (i = 0; i < ARRAY_SIZE(vsock->vqs); i++) {
		vq = &vsock->vqs[i];

		mutex_lock(&vq->mutex);
		vq->private_data = NULL;
		mutex_unlock(&vq->mutex);
	}
err:
	mutex_unlock(&vsock->dev.mutex);
	return ret;
}