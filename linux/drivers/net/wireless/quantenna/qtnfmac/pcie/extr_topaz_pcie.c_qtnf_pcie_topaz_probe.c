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
struct qtnf_shm_ipc_int {struct qtnf_pcie_topaz_state* arg; int /*<<< orphan*/  fn; } ;
struct TYPE_4__ {int /*<<< orphan*/  reclaim_tq; scalar_t__ msi_enabled; TYPE_1__* epmem_bar; struct pci_dev* pdev; } ;
struct qtnf_pcie_topaz_state {TYPE_1__* bda; TYPE_2__ base; } ;
struct qtnf_bus {int /*<<< orphan*/  mux_napi; int /*<<< orphan*/  mux_dev; int /*<<< orphan*/  fw_work; int /*<<< orphan*/ * bus_ops; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bda_shm_reg2; int /*<<< orphan*/  bda_shm_reg1; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long IRQF_NOBALANCING ; 
 unsigned long IRQF_SHARED ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,char*,void*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 struct qtnf_pcie_topaz_state* get_bus_priv (struct qtnf_bus*) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  qtnf_pcie_init_shm_ipc (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct qtnf_shm_ipc_int*) ; 
 int /*<<< orphan*/  qtnf_pcie_topaz_bus_ops ; 
 int qtnf_pcie_topaz_init_xfer (struct qtnf_pcie_topaz_state*,unsigned int) ; 
 int /*<<< orphan*/  qtnf_pcie_topaz_interrupt ; 
 int qtnf_pre_init_ep (struct qtnf_bus*) ; 
 int /*<<< orphan*/  qtnf_reclaim_tasklet_fn ; 
 int /*<<< orphan*/  qtnf_topaz_fw_work_handler ; 
 int /*<<< orphan*/  qtnf_topaz_ipc_gen_ep_int ; 
 int /*<<< orphan*/  qtnf_topaz_rx_poll ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int qtnf_pcie_topaz_probe(struct qtnf_bus *bus, unsigned int tx_bd_num)
{
	struct qtnf_pcie_topaz_state *ts = get_bus_priv(bus);
	struct pci_dev *pdev = ts->base.pdev;
	struct qtnf_shm_ipc_int ipc_int;
	unsigned long irqflags;
	int ret;

	bus->bus_ops = &qtnf_pcie_topaz_bus_ops;
	INIT_WORK(&bus->fw_work, qtnf_topaz_fw_work_handler);
	ts->bda = ts->base.epmem_bar;

	/* assign host msi irq before card init */
	if (ts->base.msi_enabled)
		irqflags = IRQF_NOBALANCING;
	else
		irqflags = IRQF_NOBALANCING | IRQF_SHARED;

	ret = devm_request_irq(&pdev->dev, pdev->irq,
			       &qtnf_pcie_topaz_interrupt,
			       irqflags, "qtnf_topaz_irq", (void *)bus);
	if (ret) {
		pr_err("failed to request pcie irq %d\n", pdev->irq);
		return ret;
	}

	disable_irq(pdev->irq);

	ret = qtnf_pre_init_ep(bus);
	if (ret) {
		pr_err("failed to init card\n");
		return ret;
	}

	ret = qtnf_pcie_topaz_init_xfer(ts, tx_bd_num);
	if (ret) {
		pr_err("PCIE xfer init failed\n");
		return ret;
	}

	tasklet_init(&ts->base.reclaim_tq, qtnf_reclaim_tasklet_fn,
		     (unsigned long)ts);
	netif_napi_add(&bus->mux_dev, &bus->mux_napi,
		       qtnf_topaz_rx_poll, 10);

	ipc_int.fn = qtnf_topaz_ipc_gen_ep_int;
	ipc_int.arg = ts;
	qtnf_pcie_init_shm_ipc(&ts->base, &ts->bda->bda_shm_reg1,
			       &ts->bda->bda_shm_reg2, &ipc_int);

	return 0;
}