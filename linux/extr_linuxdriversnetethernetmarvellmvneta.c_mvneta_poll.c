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
typedef  int u32 ;
struct napi_struct {int /*<<< orphan*/  dev; } ;
struct mvneta_port {int cause_rx_tx; scalar_t__ neta_armada3700; TYPE_1__* dev; int /*<<< orphan*/ * rxqs; scalar_t__ bm_priv; int /*<<< orphan*/  ports; } ;
struct mvneta_pcpu_port {int cause_rx_tx; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int MVNETA_CAUSE_LINK_CHANGE ; 
 int MVNETA_CAUSE_PHY_STATUS_CHANGE ; 
 int /*<<< orphan*/  MVNETA_INTR_MISC_CAUSE ; 
 int /*<<< orphan*/  MVNETA_INTR_NEW_CAUSE ; 
 int /*<<< orphan*/  MVNETA_INTR_NEW_MASK ; 
 int MVNETA_MISCINTR_INTR_MASK ; 
 int MVNETA_RX_INTR_MASK (int /*<<< orphan*/ ) ; 
 int MVNETA_TX_INTR_MASK (int /*<<< orphan*/ ) ; 
 int MVNETA_TX_INTR_MASK_ALL ; 
 int /*<<< orphan*/  enable_percpu_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fls (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mvneta_link_change (struct mvneta_port*) ; 
 int mvneta_rx_hwbm (struct napi_struct*,struct mvneta_port*,int,int /*<<< orphan*/ *) ; 
 int mvneta_rx_swbm (struct napi_struct*,struct mvneta_port*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvneta_tx_done_gbe (struct mvneta_port*,int) ; 
 int mvreg_read (struct mvneta_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_complete (struct napi_struct*) ; 
 int /*<<< orphan*/  napi_complete_done (struct napi_struct*,int) ; 
 struct mvneta_port* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_running (TYPE_1__*) ; 
 int /*<<< orphan*/  rxq_number ; 
 struct mvneta_pcpu_port* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txq_number ; 

__attribute__((used)) static int mvneta_poll(struct napi_struct *napi, int budget)
{
	int rx_done = 0;
	u32 cause_rx_tx;
	int rx_queue;
	struct mvneta_port *pp = netdev_priv(napi->dev);
	struct mvneta_pcpu_port *port = this_cpu_ptr(pp->ports);

	if (!netif_running(pp->dev)) {
		napi_complete(napi);
		return rx_done;
	}

	/* Read cause register */
	cause_rx_tx = mvreg_read(pp, MVNETA_INTR_NEW_CAUSE);
	if (cause_rx_tx & MVNETA_MISCINTR_INTR_MASK) {
		u32 cause_misc = mvreg_read(pp, MVNETA_INTR_MISC_CAUSE);

		mvreg_write(pp, MVNETA_INTR_MISC_CAUSE, 0);

		if (cause_misc & (MVNETA_CAUSE_PHY_STATUS_CHANGE |
				  MVNETA_CAUSE_LINK_CHANGE))
			mvneta_link_change(pp);
	}

	/* Release Tx descriptors */
	if (cause_rx_tx & MVNETA_TX_INTR_MASK_ALL) {
		mvneta_tx_done_gbe(pp, (cause_rx_tx & MVNETA_TX_INTR_MASK_ALL));
		cause_rx_tx &= ~MVNETA_TX_INTR_MASK_ALL;
	}

	/* For the case where the last mvneta_poll did not process all
	 * RX packets
	 */
	rx_queue = fls(((cause_rx_tx >> 8) & 0xff));

	cause_rx_tx |= pp->neta_armada3700 ? pp->cause_rx_tx :
		port->cause_rx_tx;

	if (rx_queue) {
		rx_queue = rx_queue - 1;
		if (pp->bm_priv)
			rx_done = mvneta_rx_hwbm(napi, pp, budget,
						 &pp->rxqs[rx_queue]);
		else
			rx_done = mvneta_rx_swbm(napi, pp, budget,
						 &pp->rxqs[rx_queue]);
	}

	if (rx_done < budget) {
		cause_rx_tx = 0;
		napi_complete_done(napi, rx_done);

		if (pp->neta_armada3700) {
			unsigned long flags;

			local_irq_save(flags);
			mvreg_write(pp, MVNETA_INTR_NEW_MASK,
				    MVNETA_RX_INTR_MASK(rxq_number) |
				    MVNETA_TX_INTR_MASK(txq_number) |
				    MVNETA_MISCINTR_INTR_MASK);
			local_irq_restore(flags);
		} else {
			enable_percpu_irq(pp->dev->irq, 0);
		}
	}

	if (pp->neta_armada3700)
		pp->cause_rx_tx = cause_rx_tx;
	else
		port->cause_rx_tx = cause_rx_tx;

	return rx_done;
}