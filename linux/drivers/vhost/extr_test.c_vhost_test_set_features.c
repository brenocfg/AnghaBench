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
typedef  int u64 ;
struct vhost_virtqueue {int acked_features; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct vhost_test {TYPE_1__ dev; struct vhost_virtqueue* vqs; } ;

/* Variables and functions */
 int EFAULT ; 
 int VHOST_F_LOG_ALL ; 
 size_t VHOST_TEST_VQ ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_log_access_ok (TYPE_1__*) ; 

__attribute__((used)) static int vhost_test_set_features(struct vhost_test *n, u64 features)
{
	struct vhost_virtqueue *vq;

	mutex_lock(&n->dev.mutex);
	if ((features & (1 << VHOST_F_LOG_ALL)) &&
	    !vhost_log_access_ok(&n->dev)) {
		mutex_unlock(&n->dev.mutex);
		return -EFAULT;
	}
	vq = &n->vqs[VHOST_TEST_VQ];
	mutex_lock(&vq->mutex);
	vq->acked_features = features;
	mutex_unlock(&vq->mutex);
	mutex_unlock(&n->dev.mutex);
	return 0;
}