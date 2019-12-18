#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qtnf_shm_ipc_int {struct qtnf_pcie_pearl_state* arg; int /*<<< orphan*/  fn; } ;
struct TYPE_4__ {int /*<<< orphan*/  reclaim_tq; int /*<<< orphan*/  msi_enabled; TYPE_1__* epmem_bar; int /*<<< orphan*/  dmareg_bar; struct pci_dev* pdev; } ;
struct qtnf_pcie_pearl_state {TYPE_1__* bda; TYPE_2__ base; int /*<<< orphan*/  pcie_reg_base; int /*<<< orphan*/  irq_lock; } ;
struct qtnf_bus {int /*<<< orphan*/  mux_napi; int /*<<< orphan*/  mux_dev; int /*<<< orphan*/  fw_work; int /*<<< orphan*/ * bus_ops; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bda_shm_reg2; int /*<<< orphan*/  bda_shm_reg1; int /*<<< orphan*/  bda_rc_msi_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,void*) ; 
 struct qtnf_pcie_pearl_state* get_bus_priv (struct qtnf_bus*) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  qtnf_disable_hdp_irqs (struct qtnf_pcie_pearl_state*) ; 
 int /*<<< orphan*/  qtnf_init_hdp_irqs (struct qtnf_pcie_pearl_state*) ; 
 int /*<<< orphan*/  qtnf_pcie_init_shm_ipc (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct qtnf_shm_ipc_int*) ; 
 int /*<<< orphan*/  qtnf_pcie_pearl_bus_ops ; 
 int qtnf_pcie_pearl_init_xfer (struct qtnf_pcie_pearl_state*,unsigned int) ; 
 int /*<<< orphan*/  qtnf_pcie_pearl_interrupt ; 
 int /*<<< orphan*/  qtnf_pcie_pearl_ipc_gen_ep_int ; 
 int /*<<< orphan*/  qtnf_pcie_pearl_rx_poll ; 
 int /*<<< orphan*/  qtnf_pearl_free_xfer_buffers (struct qtnf_pcie_pearl_state*) ; 
 int /*<<< orphan*/  qtnf_pearl_fw_work_handler ; 
 int /*<<< orphan*/  qtnf_pearl_reclaim_tasklet_fn ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qtnf_pcie_pearl_probe(struct qtnf_bus *bus, unsigned int tx_bd_size)
{
	struct qtnf_shm_ipc_int ipc_int;
	struct qtnf_pcie_pearl_state *ps = get_bus_priv(bus);
	struct pci_dev *pdev = ps->base.pdev;
	int ret;

	bus->bus_ops = &qtnf_pcie_pearl_bus_ops;
	spin_lock_init(&ps->irq_lock);
	INIT_WORK(&bus->fw_work, qtnf_pearl_fw_work_handler);

	ps->pcie_reg_base = ps->base.dmareg_bar;
	ps->bda = ps->base.epmem_bar;
	writel(ps->base.msi_enabled, &ps->bda->bda_rc_msi_enabled);

	ret = qtnf_pcie_pearl_init_xfer(ps, tx_bd_size);
	if (ret) {
		pr_err("PCIE xfer init failed\n");
		return ret;
	}

	/* init default irq settings */
	qtnf_init_hdp_irqs(ps);

	/* start with disabled irqs */
	qtnf_disable_hdp_irqs(ps);

	ret = devm_request_irq(&pdev->dev, pdev->irq,
			       &qtnf_pcie_pearl_interrupt, 0,
			       "qtnf_pearl_irq", (void *)bus);
	if (ret) {
		pr_err("failed to request pcie irq %d\n", pdev->irq);
		qtnf_pearl_free_xfer_buffers(ps);
		return ret;
	}

	tasklet_init(&ps->base.reclaim_tq, qtnf_pearl_reclaim_tasklet_fn,
		     (unsigned long)ps);
	netif_napi_add(&bus->mux_dev, &bus->mux_napi,
		       qtnf_pcie_pearl_rx_poll, 10);

	ipc_int.fn = qtnf_pcie_pearl_ipc_gen_ep_int;
	ipc_int.arg = ps;
	qtnf_pcie_init_shm_ipc(&ps->base, &ps->bda->bda_shm_reg1,
			       &ps->bda->bda_shm_reg2, &ipc_int);

	return 0;
}