#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_9__ {int /*<<< orphan*/  parent; struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct omap_ssi_port {size_t port_id; TYPE_1__* pdev; int /*<<< orphan*/ * dev; int /*<<< orphan*/  wk_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  ssr_dma; int /*<<< orphan*/  ssr_base; int /*<<< orphan*/  sst_dma; int /*<<< orphan*/  sst_base; int /*<<< orphan*/  work; int /*<<< orphan*/  errqueue_work; struct gpio_desc* wake_gpio; } ;
struct omap_ssi_controller {int /*<<< orphan*/  dir; struct omap_ssi_port** port; } ;
struct hsi_port {int /*<<< orphan*/  device; int /*<<< orphan*/  release; int /*<<< orphan*/  stop_tx; int /*<<< orphan*/  start_tx; int /*<<< orphan*/  flush; int /*<<< orphan*/  setup; int /*<<< orphan*/  async; } ;
struct hsi_controller {size_t num_ports; struct hsi_port** port; } ;
struct gpio_desc {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct hsi_controller* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,size_t) ; 
 struct gpio_desc* devm_gpiod_get (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 struct omap_ssi_port* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsi_add_clients_from_dt (struct hsi_port*,struct device_node*) ; 
 struct omap_ssi_controller* hsi_controller_drvdata (struct hsi_controller*) ; 
 int /*<<< orphan*/  hsi_port_set_drvdata (struct hsi_port*,struct omap_ssi_port*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct hsi_port*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssi_async ; 
 int ssi_debug_add_port (struct omap_ssi_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssi_flush ; 
 int ssi_port_get_iomem (struct platform_device*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ssi_port_irq (struct hsi_port*,struct platform_device*) ; 
 int /*<<< orphan*/  ssi_process_errqueue ; 
 int /*<<< orphan*/  ssi_queues_init (struct omap_ssi_port*) ; 
 int /*<<< orphan*/  ssi_release ; 
 int /*<<< orphan*/  ssi_setup ; 
 int /*<<< orphan*/  ssi_start_tx ; 
 int /*<<< orphan*/  ssi_stop_tx ; 
 int ssi_wake_irq (struct hsi_port*,struct platform_device*) ; 
 int /*<<< orphan*/  start_tx_work ; 

__attribute__((used)) static int ssi_port_probe(struct platform_device *pd)
{
	struct device_node *np = pd->dev.of_node;
	struct hsi_port *port;
	struct omap_ssi_port *omap_port;
	struct hsi_controller *ssi = dev_get_drvdata(pd->dev.parent);
	struct omap_ssi_controller *omap_ssi = hsi_controller_drvdata(ssi);
	struct gpio_desc *cawake_gpio = NULL;
	u32 port_id;
	int err;

	dev_dbg(&pd->dev, "init ssi port...\n");

	if (!ssi->port || !omap_ssi->port) {
		dev_err(&pd->dev, "ssi controller not initialized!\n");
		err = -ENODEV;
		goto error;
	}

	/* get id of first uninitialized port in controller */
	for (port_id = 0; port_id < ssi->num_ports && omap_ssi->port[port_id];
		port_id++)
		;

	if (port_id >= ssi->num_ports) {
		dev_err(&pd->dev, "port id out of range!\n");
		err = -ENODEV;
		goto error;
	}

	port = ssi->port[port_id];

	if (!np) {
		dev_err(&pd->dev, "missing device tree data\n");
		err = -EINVAL;
		goto error;
	}

	cawake_gpio = devm_gpiod_get(&pd->dev, "ti,ssi-cawake", GPIOD_IN);
	if (IS_ERR(cawake_gpio)) {
		err = PTR_ERR(cawake_gpio);
		dev_err(&pd->dev, "couldn't get cawake gpio (err=%d)!\n", err);
		goto error;
	}

	omap_port = devm_kzalloc(&port->device, sizeof(*omap_port), GFP_KERNEL);
	if (!omap_port) {
		err = -ENOMEM;
		goto error;
	}
	omap_port->wake_gpio = cawake_gpio;
	omap_port->pdev = &pd->dev;
	omap_port->port_id = port_id;

	INIT_DEFERRABLE_WORK(&omap_port->errqueue_work, ssi_process_errqueue);
	INIT_WORK(&omap_port->work, start_tx_work);

	/* initialize HSI port */
	port->async	= ssi_async;
	port->setup	= ssi_setup;
	port->flush	= ssi_flush;
	port->start_tx	= ssi_start_tx;
	port->stop_tx	= ssi_stop_tx;
	port->release	= ssi_release;
	hsi_port_set_drvdata(port, omap_port);
	omap_ssi->port[port_id] = omap_port;

	platform_set_drvdata(pd, port);

	err = ssi_port_get_iomem(pd, "tx", &omap_port->sst_base,
		&omap_port->sst_dma);
	if (err < 0)
		goto error;
	err = ssi_port_get_iomem(pd, "rx", &omap_port->ssr_base,
		&omap_port->ssr_dma);
	if (err < 0)
		goto error;

	err = ssi_port_irq(port, pd);
	if (err < 0)
		goto error;
	err = ssi_wake_irq(port, pd);
	if (err < 0)
		goto error;

	ssi_queues_init(omap_port);
	spin_lock_init(&omap_port->lock);
	spin_lock_init(&omap_port->wk_lock);
	omap_port->dev = &port->device;

	pm_runtime_use_autosuspend(omap_port->pdev);
	pm_runtime_set_autosuspend_delay(omap_port->pdev, 250);
	pm_runtime_enable(omap_port->pdev);

#ifdef CONFIG_DEBUG_FS
	err = ssi_debug_add_port(omap_port, omap_ssi->dir);
	if (err < 0) {
		pm_runtime_disable(omap_port->pdev);
		goto error;
	}
#endif

	hsi_add_clients_from_dt(port, np);

	dev_info(&pd->dev, "ssi port %u successfully initialized\n", port_id);

	return 0;

error:
	return err;
}