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
struct vhost_virtqueue {unsigned long busyloop_timeout; int /*<<< orphan*/  mutex; struct socket* private_data; } ;
struct vhost_net {int /*<<< orphan*/  dev; } ;
struct socket {int dummy; } ;

/* Variables and functions */
 unsigned long busy_clock () ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 scalar_t__ sock_has_rx_data (struct socket*) ; 
 scalar_t__ vhost_can_busy_poll (unsigned long) ; 
 int /*<<< orphan*/  vhost_disable_notify (int /*<<< orphan*/ *,struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vhost_enable_notify (int /*<<< orphan*/ *,struct vhost_virtqueue*) ; 
 scalar_t__ vhost_has_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_net_busy_poll_try_queue (struct vhost_net*,struct vhost_virtqueue*) ; 
 int /*<<< orphan*/  vhost_vq_avail_empty (int /*<<< orphan*/ *,struct vhost_virtqueue*) ; 

__attribute__((used)) static void vhost_net_busy_poll(struct vhost_net *net,
				struct vhost_virtqueue *rvq,
				struct vhost_virtqueue *tvq,
				bool *busyloop_intr,
				bool poll_rx)
{
	unsigned long busyloop_timeout;
	unsigned long endtime;
	struct socket *sock;
	struct vhost_virtqueue *vq = poll_rx ? tvq : rvq;

	/* Try to hold the vq mutex of the paired virtqueue. We can't
	 * use mutex_lock() here since we could not guarantee a
	 * consistenet lock ordering.
	 */
	if (!mutex_trylock(&vq->mutex))
		return;

	vhost_disable_notify(&net->dev, vq);
	sock = rvq->private_data;

	busyloop_timeout = poll_rx ? rvq->busyloop_timeout:
				     tvq->busyloop_timeout;

	preempt_disable();
	endtime = busy_clock() + busyloop_timeout;

	while (vhost_can_busy_poll(endtime)) {
		if (vhost_has_work(&net->dev)) {
			*busyloop_intr = true;
			break;
		}

		if ((sock_has_rx_data(sock) &&
		     !vhost_vq_avail_empty(&net->dev, rvq)) ||
		    !vhost_vq_avail_empty(&net->dev, tvq))
			break;

		cpu_relax();
	}

	preempt_enable();

	if (poll_rx || sock_has_rx_data(sock))
		vhost_net_busy_poll_try_queue(net, vq);
	else if (!poll_rx) /* On tx here, sock has no rx data. */
		vhost_enable_notify(&net->dev, rvq);

	mutex_unlock(&vq->mutex);
}