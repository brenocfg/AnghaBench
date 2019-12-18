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
struct vhost_virtqueue {int num; int /*<<< orphan*/  iov; int /*<<< orphan*/  private_data; scalar_t__ busyloop_timeout; } ;
struct vhost_net_virtqueue {struct vhost_virtqueue vq; } ;
struct vhost_net {struct vhost_net_virtqueue* vqs; } ;
struct msghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 size_t VHOST_NET_VQ_RX ; 
 int vhost_get_vq_desc (struct vhost_virtqueue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,unsigned int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_net_busy_poll (struct vhost_net*,struct vhost_virtqueue*,struct vhost_virtqueue*,int*,int) ; 
 int /*<<< orphan*/  vhost_sock_zcopy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_tx_batch (struct vhost_net*,struct vhost_net_virtqueue*,int /*<<< orphan*/ ,struct msghdr*) ; 

__attribute__((used)) static int vhost_net_tx_get_vq_desc(struct vhost_net *net,
				    struct vhost_net_virtqueue *tnvq,
				    unsigned int *out_num, unsigned int *in_num,
				    struct msghdr *msghdr, bool *busyloop_intr)
{
	struct vhost_net_virtqueue *rnvq = &net->vqs[VHOST_NET_VQ_RX];
	struct vhost_virtqueue *rvq = &rnvq->vq;
	struct vhost_virtqueue *tvq = &tnvq->vq;

	int r = vhost_get_vq_desc(tvq, tvq->iov, ARRAY_SIZE(tvq->iov),
				  out_num, in_num, NULL, NULL);

	if (r == tvq->num && tvq->busyloop_timeout) {
		/* Flush batched packets first */
		if (!vhost_sock_zcopy(tvq->private_data))
			vhost_tx_batch(net, tnvq, tvq->private_data, msghdr);

		vhost_net_busy_poll(net, rvq, tvq, busyloop_intr, false);

		r = vhost_get_vq_desc(tvq, tvq->iov, ARRAY_SIZE(tvq->iov),
				      out_num, in_num, NULL, NULL);
	}

	return r;
}