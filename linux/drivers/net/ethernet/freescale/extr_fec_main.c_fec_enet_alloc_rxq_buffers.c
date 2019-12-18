#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct fec_enet_private {scalar_t__ bufdesc_ex; struct fec_enet_priv_rx_q** rx_queue; } ;
struct TYPE_3__ {unsigned int ring_size; struct bufdesc* base; } ;
struct fec_enet_priv_rx_q {TYPE_1__ bd; struct sk_buff** rx_skbuff; } ;
struct bufdesc_ex {int /*<<< orphan*/  cbd_esc; } ;
struct bufdesc {int /*<<< orphan*/  cbd_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ENET_RX_EMPTY ; 
 int /*<<< orphan*/  BD_ENET_RX_INT ; 
 int /*<<< orphan*/  BD_SC_WRAP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FEC_ENET_RX_FRSIZE ; 
 int /*<<< orphan*/  cpu_to_fec16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_fec32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  fec_enet_free_buffers (struct net_device*) ; 
 struct bufdesc* fec_enet_get_nextdesc (struct bufdesc*,TYPE_1__*) ; 
 struct bufdesc* fec_enet_get_prevdesc (struct bufdesc*,TYPE_1__*) ; 
 scalar_t__ fec_enet_new_rxbdp (struct net_device*,struct bufdesc*,struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
fec_enet_alloc_rxq_buffers(struct net_device *ndev, unsigned int queue)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	unsigned int i;
	struct sk_buff *skb;
	struct bufdesc	*bdp;
	struct fec_enet_priv_rx_q *rxq;

	rxq = fep->rx_queue[queue];
	bdp = rxq->bd.base;
	for (i = 0; i < rxq->bd.ring_size; i++) {
		skb = netdev_alloc_skb(ndev, FEC_ENET_RX_FRSIZE);
		if (!skb)
			goto err_alloc;

		if (fec_enet_new_rxbdp(ndev, bdp, skb)) {
			dev_kfree_skb(skb);
			goto err_alloc;
		}

		rxq->rx_skbuff[i] = skb;
		bdp->cbd_sc = cpu_to_fec16(BD_ENET_RX_EMPTY);

		if (fep->bufdesc_ex) {
			struct bufdesc_ex *ebdp = (struct bufdesc_ex *)bdp;
			ebdp->cbd_esc = cpu_to_fec32(BD_ENET_RX_INT);
		}

		bdp = fec_enet_get_nextdesc(bdp, &rxq->bd);
	}

	/* Set the last buffer to wrap. */
	bdp = fec_enet_get_prevdesc(bdp, &rxq->bd);
	bdp->cbd_sc |= cpu_to_fec16(BD_SC_WRAP);
	return 0;

 err_alloc:
	fec_enet_free_buffers(ndev);
	return -ENOMEM;
}