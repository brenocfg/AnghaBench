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
struct vhost_virtqueue {int num; int /*<<< orphan*/  mutex; int /*<<< orphan*/  iov; void* private_data; } ;
struct vhost_test {int /*<<< orphan*/  dev; struct vhost_virtqueue* vqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 size_t VHOST_TEST_VQ ; 
 size_t iov_length (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vhost_add_used_and_signal (int /*<<< orphan*/ *,struct vhost_virtqueue*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_disable_notify (int /*<<< orphan*/ *,struct vhost_virtqueue*) ; 
 int vhost_enable_notify (int /*<<< orphan*/ *,struct vhost_virtqueue*) ; 
 int vhost_exceeds_weight (struct vhost_virtqueue*,int /*<<< orphan*/ ,size_t) ; 
 int vhost_get_vq_desc (struct vhost_virtqueue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vq_err (struct vhost_virtqueue*,char*,...) ; 

__attribute__((used)) static void handle_vq(struct vhost_test *n)
{
	struct vhost_virtqueue *vq = &n->vqs[VHOST_TEST_VQ];
	unsigned out, in;
	int head;
	size_t len, total_len = 0;
	void *private;

	mutex_lock(&vq->mutex);
	private = vq->private_data;
	if (!private) {
		mutex_unlock(&vq->mutex);
		return;
	}

	vhost_disable_notify(&n->dev, vq);

	for (;;) {
		head = vhost_get_vq_desc(vq, vq->iov,
					 ARRAY_SIZE(vq->iov),
					 &out, &in,
					 NULL, NULL);
		/* On error, stop handling until the next kick. */
		if (unlikely(head < 0))
			break;
		/* Nothing new?  Wait for eventfd to tell us they refilled. */
		if (head == vq->num) {
			if (unlikely(vhost_enable_notify(&n->dev, vq))) {
				vhost_disable_notify(&n->dev, vq);
				continue;
			}
			break;
		}
		if (in) {
			vq_err(vq, "Unexpected descriptor format for TX: "
			       "out %d, int %d\n", out, in);
			break;
		}
		len = iov_length(vq->iov, out);
		/* Sanity check */
		if (!len) {
			vq_err(vq, "Unexpected 0 len for TX\n");
			break;
		}
		vhost_add_used_and_signal(&n->dev, vq, head, 0);
		total_len += len;
		if (unlikely(vhost_exceeds_weight(vq, 0, total_len)))
			break;
	}

	mutex_unlock(&vq->mutex);
}