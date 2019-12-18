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
struct net_device {int dummy; } ;
struct fec_enet_private {scalar_t__ bufdesc_ex; struct fec_enet_priv_tx_q** tx_queue; } ;
struct TYPE_3__ {unsigned int ring_size; struct bufdesc* base; } ;
struct fec_enet_priv_tx_q {TYPE_1__ bd; int /*<<< orphan*/ * tx_bounce; } ;
struct bufdesc_ex {void* cbd_esc; } ;
struct bufdesc {int /*<<< orphan*/  cbd_sc; void* cbd_bufaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_ENET_TX_INT ; 
 int /*<<< orphan*/  BD_SC_WRAP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FEC_ENET_TX_FRSIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_fec16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_fec32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fec_enet_free_buffers (struct net_device*) ; 
 struct bufdesc* fec_enet_get_nextdesc (struct bufdesc*,TYPE_1__*) ; 
 struct bufdesc* fec_enet_get_prevdesc (struct bufdesc*,TYPE_1__*) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int
fec_enet_alloc_txq_buffers(struct net_device *ndev, unsigned int queue)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	unsigned int i;
	struct bufdesc  *bdp;
	struct fec_enet_priv_tx_q *txq;

	txq = fep->tx_queue[queue];
	bdp = txq->bd.base;
	for (i = 0; i < txq->bd.ring_size; i++) {
		txq->tx_bounce[i] = kmalloc(FEC_ENET_TX_FRSIZE, GFP_KERNEL);
		if (!txq->tx_bounce[i])
			goto err_alloc;

		bdp->cbd_sc = cpu_to_fec16(0);
		bdp->cbd_bufaddr = cpu_to_fec32(0);

		if (fep->bufdesc_ex) {
			struct bufdesc_ex *ebdp = (struct bufdesc_ex *)bdp;
			ebdp->cbd_esc = cpu_to_fec32(BD_ENET_TX_INT);
		}

		bdp = fec_enet_get_nextdesc(bdp, &txq->bd);
	}

	/* Set the last buffer to wrap. */
	bdp = fec_enet_get_prevdesc(bdp, &txq->bd);
	bdp->cbd_sc |= cpu_to_fec16(BD_SC_WRAP);

	return 0;

 err_alloc:
	fec_enet_free_buffers(ndev);
	return -ENOMEM;
}