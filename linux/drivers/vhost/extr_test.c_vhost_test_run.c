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
struct vhost_virtqueue {int /*<<< orphan*/  mutex; void* private_data; } ;
struct TYPE_2__ {int nvqs; int /*<<< orphan*/  mutex; } ;
struct vhost_test {TYPE_1__ dev; struct vhost_virtqueue* vqs; } ;

/* Variables and functions */
 int EFAULT ; 
 long EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vhost_dev_check_owner (TYPE_1__*) ; 
 int /*<<< orphan*/  vhost_test_flush_vq (struct vhost_test*,int) ; 
 int /*<<< orphan*/  vhost_vq_access_ok (struct vhost_virtqueue*) ; 
 int vhost_vq_init_access (struct vhost_virtqueue*) ; 

__attribute__((used)) static long vhost_test_run(struct vhost_test *n, int test)
{
	void *priv, *oldpriv;
	struct vhost_virtqueue *vq;
	int r, index;

	if (test < 0 || test > 1)
		return -EINVAL;

	mutex_lock(&n->dev.mutex);
	r = vhost_dev_check_owner(&n->dev);
	if (r)
		goto err;

	for (index = 0; index < n->dev.nvqs; ++index) {
		/* Verify that ring has been setup correctly. */
		if (!vhost_vq_access_ok(&n->vqs[index])) {
			r = -EFAULT;
			goto err;
		}
	}

	for (index = 0; index < n->dev.nvqs; ++index) {
		vq = n->vqs + index;
		mutex_lock(&vq->mutex);
		priv = test ? n : NULL;

		/* start polling new socket */
		oldpriv = vq->private_data;
		vq->private_data = priv;

		r = vhost_vq_init_access(&n->vqs[index]);

		mutex_unlock(&vq->mutex);

		if (r)
			goto err;

		if (oldpriv) {
			vhost_test_flush_vq(n, index);
		}
	}

	mutex_unlock(&n->dev.mutex);
	return 0;

err:
	mutex_unlock(&n->dev.mutex);
	return r;
}