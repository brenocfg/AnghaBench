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
struct vhost_virtqueue {int num; } ;
struct vhost_net_virtqueue {unsigned int vhost_hlen; struct vhost_virtqueue vq; } ;
struct vhost_net {int dummy; } ;
struct msghdr {int /*<<< orphan*/  msg_iter; } ;

/* Variables and functions */
 int EFAULT ; 
 size_t init_iov_iter (struct vhost_virtqueue*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int vhost_net_tx_get_vq_desc (struct vhost_net*,struct vhost_net_virtqueue*,unsigned int*,unsigned int*,struct msghdr*,int*) ; 
 int /*<<< orphan*/  vq_err (struct vhost_virtqueue*,char*,size_t,unsigned int) ; 

__attribute__((used)) static int get_tx_bufs(struct vhost_net *net,
		       struct vhost_net_virtqueue *nvq,
		       struct msghdr *msg,
		       unsigned int *out, unsigned int *in,
		       size_t *len, bool *busyloop_intr)
{
	struct vhost_virtqueue *vq = &nvq->vq;
	int ret;

	ret = vhost_net_tx_get_vq_desc(net, nvq, out, in, msg, busyloop_intr);

	if (ret < 0 || ret == vq->num)
		return ret;

	if (*in) {
		vq_err(vq, "Unexpected descriptor format for TX: out %d, int %d\n",
			*out, *in);
		return -EFAULT;
	}

	/* Sanity check */
	*len = init_iov_iter(vq, &msg->msg_iter, nvq->vhost_hlen, *out);
	if (*len == 0) {
		vq_err(vq, "Unexpected header len for TX: %zd expected %zd\n",
			*len, nvq->vhost_hlen);
		return -EFAULT;
	}

	return ret;
}