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
struct vhost_virtqueue {scalar_t__ busyloop_timeout; } ;
struct vhost_net_virtqueue {struct vhost_virtqueue vq; } ;
struct vhost_net {struct vhost_net_virtqueue* vqs; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 size_t VHOST_NET_VQ_RX ; 
 size_t VHOST_NET_VQ_TX ; 
 int peek_head_len (struct vhost_net_virtqueue*,struct sock*) ; 
 int /*<<< orphan*/  vhost_net_busy_poll (struct vhost_net*,struct vhost_virtqueue*,struct vhost_virtqueue*,int*,int) ; 
 int /*<<< orphan*/  vhost_net_signal_used (struct vhost_net_virtqueue*) ; 

__attribute__((used)) static int vhost_net_rx_peek_head_len(struct vhost_net *net, struct sock *sk,
				      bool *busyloop_intr)
{
	struct vhost_net_virtqueue *rnvq = &net->vqs[VHOST_NET_VQ_RX];
	struct vhost_net_virtqueue *tnvq = &net->vqs[VHOST_NET_VQ_TX];
	struct vhost_virtqueue *rvq = &rnvq->vq;
	struct vhost_virtqueue *tvq = &tnvq->vq;
	int len = peek_head_len(rnvq, sk);

	if (!len && rvq->busyloop_timeout) {
		/* Flush batched heads first */
		vhost_net_signal_used(rnvq);
		/* Both tx vq and rx socket were polled here */
		vhost_net_busy_poll(net, rvq, tvq, busyloop_intr, true);

		len = peek_head_len(rnvq, sk);
	}

	return len;
}