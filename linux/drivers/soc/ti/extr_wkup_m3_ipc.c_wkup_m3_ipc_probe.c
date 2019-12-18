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
struct TYPE_2__ {int tx_block; int knows_txdone; int /*<<< orphan*/ * rx_callback; int /*<<< orphan*/ * tx_prepare; int /*<<< orphan*/ * tx_done; struct device* dev; } ;
struct wkup_m3_ipc {struct task_struct* mbox; int /*<<< orphan*/ * ops; int /*<<< orphan*/  state; struct device* dev; struct rproc* rproc; TYPE_1__ mbox_client; struct task_struct* ipc_mem_base; } ;
struct task_struct {int dummy; } ;
struct rproc {int dummy; } ;
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
typedef  int /*<<< orphan*/  phandle ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  M3_STATE_RESET ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct task_struct* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct wkup_m3_ipc* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct wkup_m3_ipc*) ; 
 int /*<<< orphan*/  ipc_ops ; 
 struct task_struct* kthread_run (void*,struct wkup_m3_ipc*,char*) ; 
 struct wkup_m3_ipc* m3_ipc_state ; 
 int /*<<< orphan*/  mbox_free_channel (struct task_struct*) ; 
 struct task_struct* mbox_request_channel (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rproc* rproc_get_by_phandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rproc_put (struct rproc*) ; 
 scalar_t__ wkup_m3_rproc_boot_thread ; 
 int /*<<< orphan*/  wkup_m3_txev_handler ; 

__attribute__((used)) static int wkup_m3_ipc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int irq, ret;
	phandle rproc_phandle;
	struct rproc *m3_rproc;
	struct resource *res;
	struct task_struct *task;
	struct wkup_m3_ipc *m3_ipc;

	m3_ipc = devm_kzalloc(dev, sizeof(*m3_ipc), GFP_KERNEL);
	if (!m3_ipc)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	m3_ipc->ipc_mem_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(m3_ipc->ipc_mem_base)) {
		dev_err(dev, "could not ioremap ipc_mem\n");
		return PTR_ERR(m3_ipc->ipc_mem_base);
	}

	irq = platform_get_irq(pdev, 0);
	if (!irq) {
		dev_err(&pdev->dev, "no irq resource\n");
		return -ENXIO;
	}

	ret = devm_request_irq(dev, irq, wkup_m3_txev_handler,
			       0, "wkup_m3_txev", m3_ipc);
	if (ret) {
		dev_err(dev, "request_irq failed\n");
		return ret;
	}

	m3_ipc->mbox_client.dev = dev;
	m3_ipc->mbox_client.tx_done = NULL;
	m3_ipc->mbox_client.tx_prepare = NULL;
	m3_ipc->mbox_client.rx_callback = NULL;
	m3_ipc->mbox_client.tx_block = false;
	m3_ipc->mbox_client.knows_txdone = false;

	m3_ipc->mbox = mbox_request_channel(&m3_ipc->mbox_client, 0);

	if (IS_ERR(m3_ipc->mbox)) {
		dev_err(dev, "IPC Request for A8->M3 Channel failed! %ld\n",
			PTR_ERR(m3_ipc->mbox));
		return PTR_ERR(m3_ipc->mbox);
	}

	if (of_property_read_u32(dev->of_node, "ti,rproc", &rproc_phandle)) {
		dev_err(&pdev->dev, "could not get rproc phandle\n");
		ret = -ENODEV;
		goto err_free_mbox;
	}

	m3_rproc = rproc_get_by_phandle(rproc_phandle);
	if (!m3_rproc) {
		dev_err(&pdev->dev, "could not get rproc handle\n");
		ret = -EPROBE_DEFER;
		goto err_free_mbox;
	}

	m3_ipc->rproc = m3_rproc;
	m3_ipc->dev = dev;
	m3_ipc->state = M3_STATE_RESET;

	m3_ipc->ops = &ipc_ops;

	/*
	 * Wait for firmware loading completion in a thread so we
	 * can boot the wkup_m3 as soon as it's ready without holding
	 * up kernel boot
	 */
	task = kthread_run((void *)wkup_m3_rproc_boot_thread, m3_ipc,
			   "wkup_m3_rproc_loader");

	if (IS_ERR(task)) {
		dev_err(dev, "can't create rproc_boot thread\n");
		ret = PTR_ERR(task);
		goto err_put_rproc;
	}

	m3_ipc_state = m3_ipc;

	return 0;

err_put_rproc:
	rproc_put(m3_rproc);
err_free_mbox:
	mbox_free_channel(m3_ipc->mbox);
	return ret;
}