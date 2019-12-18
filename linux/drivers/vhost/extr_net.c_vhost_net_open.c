#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xdp_buff {int dummy; } ;
typedef  void vhost_virtqueue ;
struct TYPE_7__ {int /*<<< orphan*/ * page; } ;
struct vhost_dev {int dummy; } ;
struct vhost_net {scalar_t__ refcnt_bias; TYPE_3__ page_frag; scalar_t__ poll; TYPE_2__* vqs; struct vhost_dev dev; } ;
struct inode {int dummy; } ;
struct file {struct vhost_net* private_data; } ;
struct TYPE_8__ {void** queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  handle_kick; } ;
struct TYPE_6__ {TYPE_4__ rxq; int /*<<< orphan*/ * rx_ring; scalar_t__ sock_hlen; scalar_t__ vhost_hlen; scalar_t__ batched_xdp; scalar_t__ done_idx; scalar_t__ upend_idx; int /*<<< orphan*/ * ubuf_info; int /*<<< orphan*/ * ubufs; TYPE_1__ vq; struct xdp_buff* xdp; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  EPOLLOUT ; 
 int GFP_KERNEL ; 
 scalar_t__ UIO_MAXIOV ; 
 int VHOST_NET_BATCH ; 
 int /*<<< orphan*/  VHOST_NET_PKT_WEIGHT ; 
 int VHOST_NET_VQ_MAX ; 
 size_t VHOST_NET_VQ_RX ; 
 size_t VHOST_NET_VQ_TX ; 
 int /*<<< orphan*/  VHOST_NET_WEIGHT ; 
 int __GFP_RETRY_MAYFAIL ; 
 int /*<<< orphan*/  handle_rx_kick ; 
 int /*<<< orphan*/  handle_rx_net ; 
 int /*<<< orphan*/  handle_tx_kick ; 
 int /*<<< orphan*/  handle_tx_net ; 
 int /*<<< orphan*/  kfree (void**) ; 
 void* kmalloc_array (int,int,int) ; 
 int /*<<< orphan*/  kvfree (struct vhost_net*) ; 
 struct vhost_net* kvmalloc (int,int) ; 
 int /*<<< orphan*/  vhost_dev_init (struct vhost_dev*,void**,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_net_buf_init (TYPE_4__*) ; 
 int /*<<< orphan*/  vhost_poll_init (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vhost_dev*) ; 

__attribute__((used)) static int vhost_net_open(struct inode *inode, struct file *f)
{
	struct vhost_net *n;
	struct vhost_dev *dev;
	struct vhost_virtqueue **vqs;
	void **queue;
	struct xdp_buff *xdp;
	int i;

	n = kvmalloc(sizeof *n, GFP_KERNEL | __GFP_RETRY_MAYFAIL);
	if (!n)
		return -ENOMEM;
	vqs = kmalloc_array(VHOST_NET_VQ_MAX, sizeof(*vqs), GFP_KERNEL);
	if (!vqs) {
		kvfree(n);
		return -ENOMEM;
	}

	queue = kmalloc_array(VHOST_NET_BATCH, sizeof(void *),
			      GFP_KERNEL);
	if (!queue) {
		kfree(vqs);
		kvfree(n);
		return -ENOMEM;
	}
	n->vqs[VHOST_NET_VQ_RX].rxq.queue = queue;

	xdp = kmalloc_array(VHOST_NET_BATCH, sizeof(*xdp), GFP_KERNEL);
	if (!xdp) {
		kfree(vqs);
		kvfree(n);
		kfree(queue);
		return -ENOMEM;
	}
	n->vqs[VHOST_NET_VQ_TX].xdp = xdp;

	dev = &n->dev;
	vqs[VHOST_NET_VQ_TX] = &n->vqs[VHOST_NET_VQ_TX].vq;
	vqs[VHOST_NET_VQ_RX] = &n->vqs[VHOST_NET_VQ_RX].vq;
	n->vqs[VHOST_NET_VQ_TX].vq.handle_kick = handle_tx_kick;
	n->vqs[VHOST_NET_VQ_RX].vq.handle_kick = handle_rx_kick;
	for (i = 0; i < VHOST_NET_VQ_MAX; i++) {
		n->vqs[i].ubufs = NULL;
		n->vqs[i].ubuf_info = NULL;
		n->vqs[i].upend_idx = 0;
		n->vqs[i].done_idx = 0;
		n->vqs[i].batched_xdp = 0;
		n->vqs[i].vhost_hlen = 0;
		n->vqs[i].sock_hlen = 0;
		n->vqs[i].rx_ring = NULL;
		vhost_net_buf_init(&n->vqs[i].rxq);
	}
	vhost_dev_init(dev, vqs, VHOST_NET_VQ_MAX,
		       UIO_MAXIOV + VHOST_NET_BATCH,
		       VHOST_NET_PKT_WEIGHT, VHOST_NET_WEIGHT);

	vhost_poll_init(n->poll + VHOST_NET_VQ_TX, handle_tx_net, EPOLLOUT, dev);
	vhost_poll_init(n->poll + VHOST_NET_VQ_RX, handle_rx_net, EPOLLIN, dev);

	f->private_data = n;
	n->page_frag.page = NULL;
	n->refcnt_bias = 0;

	return 0;
}