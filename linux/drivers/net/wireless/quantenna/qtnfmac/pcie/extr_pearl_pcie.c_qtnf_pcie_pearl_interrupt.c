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
typedef  int u32 ;
struct qtnf_pcie_bus_priv {int /*<<< orphan*/  msi_enabled; int /*<<< orphan*/  reclaim_tq; int /*<<< orphan*/  shm_ipc_ep_out; int /*<<< orphan*/  shm_ipc_ep_in; int /*<<< orphan*/  pcie_irq_count; } ;
struct qtnf_pcie_pearl_state {int pcie_irq_mask; int /*<<< orphan*/  pcie_reg_base; int /*<<< orphan*/  pcie_irq_uf_count; int /*<<< orphan*/  pcie_irq_tx_count; int /*<<< orphan*/  pcie_irq_rx_count; struct qtnf_pcie_bus_priv base; } ;
struct qtnf_bus {int /*<<< orphan*/  mux_napi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int PCIE_HDP_INT_HHBM_UF ; 
 int PCIE_HDP_INT_RX_BITS ; 
 int /*<<< orphan*/  PCIE_HDP_INT_STATUS (int /*<<< orphan*/ ) ; 
 int PCIE_HDP_INT_TX_BITS ; 
 struct qtnf_pcie_pearl_state* get_bus_priv (struct qtnf_bus*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qtnf_deassert_intx (struct qtnf_pcie_pearl_state*) ; 
 int /*<<< orphan*/  qtnf_dis_rxdone_irq (struct qtnf_pcie_pearl_state*) ; 
 int /*<<< orphan*/  qtnf_dis_txdone_irq (struct qtnf_pcie_pearl_state*) ; 
 int /*<<< orphan*/  qtnf_non_posted_write (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_shm_ipc_irq_handler (int /*<<< orphan*/ *) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t qtnf_pcie_pearl_interrupt(int irq, void *data)
{
	struct qtnf_bus *bus = (struct qtnf_bus *)data;
	struct qtnf_pcie_pearl_state *ps = get_bus_priv(bus);
	struct qtnf_pcie_bus_priv *priv = &ps->base;
	u32 status;

	priv->pcie_irq_count++;
	status = readl(PCIE_HDP_INT_STATUS(ps->pcie_reg_base));

	qtnf_shm_ipc_irq_handler(&priv->shm_ipc_ep_in);
	qtnf_shm_ipc_irq_handler(&priv->shm_ipc_ep_out);

	if (!(status & ps->pcie_irq_mask))
		goto irq_done;

	if (status & PCIE_HDP_INT_RX_BITS)
		ps->pcie_irq_rx_count++;

	if (status & PCIE_HDP_INT_TX_BITS)
		ps->pcie_irq_tx_count++;

	if (status & PCIE_HDP_INT_HHBM_UF)
		ps->pcie_irq_uf_count++;

	if (status & PCIE_HDP_INT_RX_BITS) {
		qtnf_dis_rxdone_irq(ps);
		napi_schedule(&bus->mux_napi);
	}

	if (status & PCIE_HDP_INT_TX_BITS) {
		qtnf_dis_txdone_irq(ps);
		tasklet_hi_schedule(&priv->reclaim_tq);
	}

irq_done:
	/* H/W workaround: clean all bits, not only enabled */
	qtnf_non_posted_write(~0U, PCIE_HDP_INT_STATUS(ps->pcie_reg_base));

	if (!priv->msi_enabled)
		qtnf_deassert_intx(ps);

	return IRQ_HANDLED;
}