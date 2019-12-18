#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mvpp2_port {int nrxqs; TYPE_2__* priv; TYPE_1__** rxqs; int /*<<< orphan*/  id; scalar_t__ base; } ;
struct TYPE_5__ {scalar_t__ hw_version; int tclk; } ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
 scalar_t__ MVPP21 ; 
 scalar_t__ MVPP2_GMAC_PORT_FIFO_CFG_1_REG ; 
 int MVPP2_GMAC_TX_FIFO_MIN_TH_ALL_MASK ; 
 int MVPP2_GMAC_TX_FIFO_MIN_TH_MASK (int) ; 
 int MVPP2_MAX_TXQ ; 
 int /*<<< orphan*/  MVPP2_RXQ_CONFIG_REG (int) ; 
 int /*<<< orphan*/  MVPP2_RX_CTRL_REG (int /*<<< orphan*/ ) ; 
 int MVPP2_RX_LOW_LATENCY_PKT_SIZE (int) ; 
 int MVPP2_RX_USE_PSEUDO_FOR_CSUM_MASK ; 
 int MVPP2_SNOOP_BUF_HDR_MASK ; 
 int MVPP2_SNOOP_PKT_SIZE_MASK ; 
 int MVPP2_TXP_REFILL_PERIOD_ALL_MASK ; 
 int MVPP2_TXP_REFILL_PERIOD_MASK (int) ; 
 int MVPP2_TXP_REFILL_TOKENS_ALL_MASK ; 
 int /*<<< orphan*/  MVPP2_TXP_SCHED_CMD_1_REG ; 
 int /*<<< orphan*/  MVPP2_TXP_SCHED_FIXED_PRIO_REG ; 
 int /*<<< orphan*/  MVPP2_TXP_SCHED_PERIOD_REG ; 
 int /*<<< orphan*/  MVPP2_TXP_SCHED_PORT_INDEX_REG ; 
 int /*<<< orphan*/  MVPP2_TXP_SCHED_REFILL_REG ; 
 int /*<<< orphan*/  MVPP2_TXP_SCHED_TOKEN_SIZE_REG ; 
 int MVPP2_TXP_TOKEN_SIZE_MAX ; 
 int /*<<< orphan*/  MVPP2_TXQ_SCHED_TOKEN_CNTR_REG (int) ; 
 int USEC_PER_SEC ; 
 int mvpp2_egress_port (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_interrupts_disable (struct mvpp2_port*) ; 
 int mvpp2_read (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_write (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mvpp2_defaults_set(struct mvpp2_port *port)
{
	int tx_port_num, val, queue, lrxq;

	if (port->priv->hw_version == MVPP21) {
		/* Update TX FIFO MIN Threshold */
		val = readl(port->base + MVPP2_GMAC_PORT_FIFO_CFG_1_REG);
		val &= ~MVPP2_GMAC_TX_FIFO_MIN_TH_ALL_MASK;
		/* Min. TX threshold must be less than minimal packet length */
		val |= MVPP2_GMAC_TX_FIFO_MIN_TH_MASK(64 - 4 - 2);
		writel(val, port->base + MVPP2_GMAC_PORT_FIFO_CFG_1_REG);
	}

	/* Disable Legacy WRR, Disable EJP, Release from reset */
	tx_port_num = mvpp2_egress_port(port);
	mvpp2_write(port->priv, MVPP2_TXP_SCHED_PORT_INDEX_REG,
		    tx_port_num);
	mvpp2_write(port->priv, MVPP2_TXP_SCHED_CMD_1_REG, 0);

	/* Set TXQ scheduling to Round-Robin */
	mvpp2_write(port->priv, MVPP2_TXP_SCHED_FIXED_PRIO_REG, 0);

	/* Close bandwidth for all queues */
	for (queue = 0; queue < MVPP2_MAX_TXQ; queue++)
		mvpp2_write(port->priv,
			    MVPP2_TXQ_SCHED_TOKEN_CNTR_REG(queue), 0);

	/* Set refill period to 1 usec, refill tokens
	 * and bucket size to maximum
	 */
	mvpp2_write(port->priv, MVPP2_TXP_SCHED_PERIOD_REG,
		    port->priv->tclk / USEC_PER_SEC);
	val = mvpp2_read(port->priv, MVPP2_TXP_SCHED_REFILL_REG);
	val &= ~MVPP2_TXP_REFILL_PERIOD_ALL_MASK;
	val |= MVPP2_TXP_REFILL_PERIOD_MASK(1);
	val |= MVPP2_TXP_REFILL_TOKENS_ALL_MASK;
	mvpp2_write(port->priv, MVPP2_TXP_SCHED_REFILL_REG, val);
	val = MVPP2_TXP_TOKEN_SIZE_MAX;
	mvpp2_write(port->priv, MVPP2_TXP_SCHED_TOKEN_SIZE_REG, val);

	/* Set MaximumLowLatencyPacketSize value to 256 */
	mvpp2_write(port->priv, MVPP2_RX_CTRL_REG(port->id),
		    MVPP2_RX_USE_PSEUDO_FOR_CSUM_MASK |
		    MVPP2_RX_LOW_LATENCY_PKT_SIZE(256));

	/* Enable Rx cache snoop */
	for (lrxq = 0; lrxq < port->nrxqs; lrxq++) {
		queue = port->rxqs[lrxq]->id;
		val = mvpp2_read(port->priv, MVPP2_RXQ_CONFIG_REG(queue));
		val |= MVPP2_SNOOP_PKT_SIZE_MASK |
			   MVPP2_SNOOP_BUF_HDR_MASK;
		mvpp2_write(port->priv, MVPP2_RXQ_CONFIG_REG(queue), val);
	}

	/* At default, mask all interrupts to all present cpus */
	mvpp2_interrupts_disable(port);
}