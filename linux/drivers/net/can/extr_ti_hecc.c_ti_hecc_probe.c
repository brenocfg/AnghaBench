#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_14__ {int /*<<< orphan*/  mb_last; int /*<<< orphan*/  mb_first; int /*<<< orphan*/  mailbox_read; } ;
struct TYPE_11__ {int /*<<< orphan*/  freq; } ;
struct TYPE_12__ {TYPE_1__ clock; int /*<<< orphan*/  ctrlmode_supported; int /*<<< orphan*/  do_get_berr_counter; int /*<<< orphan*/  do_set_mode; int /*<<< orphan*/ * bittiming_const; } ;
struct ti_hecc_priv {struct regulator* clk; TYPE_8__ offload; struct regulator* base; TYPE_2__ can; int /*<<< orphan*/  mbx_lock; int /*<<< orphan*/  use_hecc1int; struct regulator* reg_xceiver; struct net_device* ndev; struct regulator* mbx; struct regulator* hecc_ram; } ;
struct resource {scalar_t__ start; } ;
struct regulator {int dummy; } ;
struct TYPE_13__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct net_device {scalar_t__ irq; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  flags; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_CTRLMODE_3_SAMPLES ; 
 int /*<<< orphan*/  CONFIG_OF ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  HECC_MAX_TX_MBOX ; 
 int /*<<< orphan*/  HECC_RX_FIRST_MBOX ; 
 int /*<<< orphan*/  HECC_RX_LAST_MBOX ; 
 int /*<<< orphan*/  IFF_ECHO ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 int PTR_ERR (struct regulator*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_3__*) ; 
 struct net_device* alloc_candev (int,int /*<<< orphan*/ ) ; 
 int can_rx_offload_add_timestamp (struct net_device*,TYPE_8__*) ; 
 int /*<<< orphan*/  can_rx_offload_del (TYPE_8__*) ; 
 struct regulator* clk_get (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  clk_get_rate (struct regulator*) ; 
 int clk_prepare_enable (struct regulator*) ; 
 int /*<<< orphan*/  clk_put (struct regulator*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,struct regulator*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_can_led_init (struct net_device*) ; 
 void* devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct regulator* devm_regulator_get (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  free_candev (struct net_device*) ; 
 struct ti_hecc_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int register_candev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ti_hecc_bittiming_const ; 
 int /*<<< orphan*/  ti_hecc_do_set_mode ; 
 int /*<<< orphan*/  ti_hecc_get_berr_counter ; 
 int /*<<< orphan*/  ti_hecc_mailbox_read ; 
 int /*<<< orphan*/  ti_hecc_netdev_ops ; 

__attribute__((used)) static int ti_hecc_probe(struct platform_device *pdev)
{
	struct net_device *ndev = (struct net_device *)0;
	struct ti_hecc_priv *priv;
	struct device_node *np = pdev->dev.of_node;
	struct resource *res, *irq;
	struct regulator *reg_xceiver;
	int err = -ENODEV;

	if (!IS_ENABLED(CONFIG_OF) || !np)
		return -EINVAL;

	reg_xceiver = devm_regulator_get(&pdev->dev, "xceiver");
	if (PTR_ERR(reg_xceiver) == -EPROBE_DEFER)
		return -EPROBE_DEFER;
	else if (IS_ERR(reg_xceiver))
		reg_xceiver = NULL;

	ndev = alloc_candev(sizeof(struct ti_hecc_priv), HECC_MAX_TX_MBOX);
	if (!ndev) {
		dev_err(&pdev->dev, "alloc_candev failed\n");
		return -ENOMEM;
	}
	priv = netdev_priv(ndev);

	/* handle hecc memory */
	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "hecc");
	if (!res) {
		dev_err(&pdev->dev, "can't get IORESOURCE_MEM hecc\n");
		return -EINVAL;
	}

	priv->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->base)) {
		dev_err(&pdev->dev, "hecc ioremap failed\n");
		return PTR_ERR(priv->base);
	}

	/* handle hecc-ram memory */
	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "hecc-ram");
	if (!res) {
		dev_err(&pdev->dev, "can't get IORESOURCE_MEM hecc-ram\n");
		return -EINVAL;
	}

	priv->hecc_ram = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->hecc_ram)) {
		dev_err(&pdev->dev, "hecc-ram ioremap failed\n");
		return PTR_ERR(priv->hecc_ram);
	}

	/* handle mbx memory */
	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "mbx");
	if (!res) {
		dev_err(&pdev->dev, "can't get IORESOURCE_MEM mbx\n");
		return -EINVAL;
	}

	priv->mbx = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->mbx)) {
		dev_err(&pdev->dev, "mbx ioremap failed\n");
		return PTR_ERR(priv->mbx);
	}

	irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!irq) {
		dev_err(&pdev->dev, "No irq resource\n");
		goto probe_exit;
	}

	priv->ndev = ndev;
	priv->reg_xceiver = reg_xceiver;
	priv->use_hecc1int = of_property_read_bool(np, "ti,use-hecc1int");

	priv->can.bittiming_const = &ti_hecc_bittiming_const;
	priv->can.do_set_mode = ti_hecc_do_set_mode;
	priv->can.do_get_berr_counter = ti_hecc_get_berr_counter;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_3_SAMPLES;

	spin_lock_init(&priv->mbx_lock);
	ndev->irq = irq->start;
	ndev->flags |= IFF_ECHO;
	platform_set_drvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);
	ndev->netdev_ops = &ti_hecc_netdev_ops;

	priv->clk = clk_get(&pdev->dev, "hecc_ck");
	if (IS_ERR(priv->clk)) {
		dev_err(&pdev->dev, "No clock available\n");
		err = PTR_ERR(priv->clk);
		priv->clk = NULL;
		goto probe_exit_candev;
	}
	priv->can.clock.freq = clk_get_rate(priv->clk);

	err = clk_prepare_enable(priv->clk);
	if (err) {
		dev_err(&pdev->dev, "clk_prepare_enable() failed\n");
		goto probe_exit_clk;
	}

	priv->offload.mailbox_read = ti_hecc_mailbox_read;
	priv->offload.mb_first = HECC_RX_FIRST_MBOX;
	priv->offload.mb_last = HECC_RX_LAST_MBOX;
	err = can_rx_offload_add_timestamp(ndev, &priv->offload);
	if (err) {
		dev_err(&pdev->dev, "can_rx_offload_add_timestamp() failed\n");
		goto probe_exit_clk;
	}

	err = register_candev(ndev);
	if (err) {
		dev_err(&pdev->dev, "register_candev() failed\n");
		goto probe_exit_offload;
	}

	devm_can_led_init(ndev);

	dev_info(&pdev->dev, "device registered (reg_base=%p, irq=%u)\n",
		 priv->base, (u32)ndev->irq);

	return 0;

probe_exit_offload:
	can_rx_offload_del(&priv->offload);
probe_exit_clk:
	clk_put(priv->clk);
probe_exit_candev:
	free_candev(ndev);
probe_exit:
	return err;
}