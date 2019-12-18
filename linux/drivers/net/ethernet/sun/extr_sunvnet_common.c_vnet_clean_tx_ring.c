#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lp; struct vio_dring_state* drings; } ;
struct vnet_port {TYPE_2__* tx_bufs; TYPE_1__ vio; } ;
struct TYPE_6__ {scalar_t__ state; } ;
struct vio_net_desc {TYPE_3__ hdr; } ;
struct vio_dring_state {int prod; } ;
struct sk_buff {struct sk_buff* next; } ;
struct TYPE_5__ {int /*<<< orphan*/  ncookies; int /*<<< orphan*/  cookies; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct sk_buff*) ; 
 scalar_t__ VIO_DESC_DONE ; 
 scalar_t__ VIO_DESC_FREE ; 
 scalar_t__ VIO_DESC_READY ; 
 size_t VIO_DRIVER_TX_RING ; 
 int VNET_TX_RING_SIZE ; 
 int /*<<< orphan*/  ldc_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,scalar_t__) ; 
 struct vio_net_desc* vio_dring_entry (struct vio_dring_state*,int) ; 

__attribute__((used)) static struct sk_buff *vnet_clean_tx_ring(struct vnet_port *port,
					  unsigned *pending)
{
	struct vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_TX_RING];
	struct sk_buff *skb = NULL;
	int i, txi;

	*pending = 0;

	txi = dr->prod;
	for (i = 0; i < VNET_TX_RING_SIZE; ++i) {
		struct vio_net_desc *d;

		--txi;
		if (txi < 0)
			txi = VNET_TX_RING_SIZE - 1;

		d = vio_dring_entry(dr, txi);

		if (d->hdr.state == VIO_DESC_READY) {
			(*pending)++;
			continue;
		}
		if (port->tx_bufs[txi].skb) {
			if (d->hdr.state != VIO_DESC_DONE)
				pr_notice("invalid ring buffer state %d\n",
					  d->hdr.state);
			BUG_ON(port->tx_bufs[txi].skb->next);

			port->tx_bufs[txi].skb->next = skb;
			skb = port->tx_bufs[txi].skb;
			port->tx_bufs[txi].skb = NULL;

			ldc_unmap(port->vio.lp,
				  port->tx_bufs[txi].cookies,
				  port->tx_bufs[txi].ncookies);
		} else if (d->hdr.state == VIO_DESC_FREE) {
			break;
		}
		d->hdr.state = VIO_DESC_FREE;
	}
	return skb;
}