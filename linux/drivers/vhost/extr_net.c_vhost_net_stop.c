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
struct vhost_net {TYPE_1__* vqs; } ;
struct socket {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vq; } ;

/* Variables and functions */
 size_t VHOST_NET_VQ_RX ; 
 size_t VHOST_NET_VQ_TX ; 
 struct socket* vhost_net_stop_vq (struct vhost_net*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vhost_net_stop(struct vhost_net *n, struct socket **tx_sock,
			   struct socket **rx_sock)
{
	*tx_sock = vhost_net_stop_vq(n, &n->vqs[VHOST_NET_VQ_TX].vq);
	*rx_sock = vhost_net_stop_vq(n, &n->vqs[VHOST_NET_VQ_RX].vq);
}