#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; int /*<<< orphan*/  name; TYPE_1__* id_entry; } ;
struct of_device_id {TYPE_1__* data; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct fec_platform_data {int phy; } ;
struct fec_enet_private {int quirks; int num_rx_queues; int num_tx_queues; int wol_flag; int phy_interface; int ptp_clk_on; int bufdesc_ex; int* irq; int /*<<< orphan*/ * clk_ipg; int /*<<< orphan*/ * clk_ahb; int /*<<< orphan*/ * reg_phy; int /*<<< orphan*/  tx_timeout_work; int /*<<< orphan*/  rx_copybreak; int /*<<< orphan*/  dev_id; scalar_t__ ptp_clock; int /*<<< orphan*/  mdio_done; int /*<<< orphan*/ * clk_ptp; int /*<<< orphan*/ * clk_ref; int /*<<< orphan*/  ptp_clk_mutex; int /*<<< orphan*/ * clk_enet_out; int /*<<< orphan*/  itr_clk_rate; struct device_node* phy_node; struct platform_device* pdev; int /*<<< orphan*/ * hwp; int /*<<< orphan*/  pause_flag; struct net_device* netdev; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  irq_name ;
struct TYPE_20__ {int driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPYBREAK_DEFAULT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  FEC_MDIO_PM_TIMEOUT ; 
 int /*<<< orphan*/  FEC_PAUSE_FLAG_AUTONEG ; 
 int FEC_QUIRK_ERR006687 ; 
 int FEC_QUIRK_HAS_BUFDESC_EX ; 
 int FEC_QUIRK_HAS_GBIT ; 
 scalar_t__ FEC_STATS_SIZE ; 
 int FEC_WOL_HAS_MAGIC_PACKET ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PHY_INTERFACE_MODE_MII ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_2__*) ; 
 struct net_device* alloc_etherdev_mqs (scalar_t__,int,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 struct fec_platform_data* dev_get_platdata (TYPE_2__*) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 void* devm_clk_get (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_regulator_get_optional (TYPE_2__*,char*) ; 
 int devm_request_irq (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  fec_dt_ids ; 
 int fec_enet_clk_enable (struct net_device*,int) ; 
 int fec_enet_get_irq_cnt (struct platform_device*) ; 
 int /*<<< orphan*/  fec_enet_get_queue_num (struct platform_device*,int*,int*) ; 
 int fec_enet_init (struct net_device*) ; 
 int /*<<< orphan*/  fec_enet_interrupt ; 
 int fec_enet_mii_init (struct platform_device*) ; 
 int /*<<< orphan*/  fec_enet_mii_remove (struct fec_enet_private*) ; 
 int /*<<< orphan*/  fec_enet_timeout_work ; 
 int /*<<< orphan*/  fec_ptp_init (struct platform_device*,int) ; 
 int /*<<< orphan*/  fec_ptp_stop (struct platform_device*) ; 
 int fec_reset_phy (struct platform_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int of_get_phy_mode (struct device_node*) ; 
 scalar_t__ of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_machine_is_compatible (char*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct device_node* of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_phy_deregister_fixed_link (struct device_node*) ; 
 scalar_t__ of_phy_is_fixed_link (struct device_node*) ; 
 int of_phy_register_fixed_link (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  pinctrl_pm_select_default_state (TYPE_2__*) ; 
 int /*<<< orphan*/  pinctrl_pm_select_sleep_state (TYPE_2__*) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 int platform_get_irq_byname_optional (struct platform_device*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_2__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_2__*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ *) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
fec_probe(struct platform_device *pdev)
{
	struct fec_enet_private *fep;
	struct fec_platform_data *pdata;
	struct net_device *ndev;
	int i, irq, ret = 0;
	const struct of_device_id *of_id;
	static int dev_id;
	struct device_node *np = pdev->dev.of_node, *phy_node;
	int num_tx_qs;
	int num_rx_qs;
	char irq_name[8];
	int irq_cnt;

	fec_enet_get_queue_num(pdev, &num_tx_qs, &num_rx_qs);

	/* Init network device */
	ndev = alloc_etherdev_mqs(sizeof(struct fec_enet_private) +
				  FEC_STATS_SIZE, num_tx_qs, num_rx_qs);
	if (!ndev)
		return -ENOMEM;

	SET_NETDEV_DEV(ndev, &pdev->dev);

	/* setup board info structure */
	fep = netdev_priv(ndev);

	of_id = of_match_device(fec_dt_ids, &pdev->dev);
	if (of_id)
		pdev->id_entry = of_id->data;
	fep->quirks = pdev->id_entry->driver_data;

	fep->netdev = ndev;
	fep->num_rx_queues = num_rx_qs;
	fep->num_tx_queues = num_tx_qs;

#if !defined(CONFIG_M5272)
	/* default enable pause frame auto negotiation */
	if (fep->quirks & FEC_QUIRK_HAS_GBIT)
		fep->pause_flag |= FEC_PAUSE_FLAG_AUTONEG;
#endif

	/* Select default pin state */
	pinctrl_pm_select_default_state(&pdev->dev);

	fep->hwp = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(fep->hwp)) {
		ret = PTR_ERR(fep->hwp);
		goto failed_ioremap;
	}

	fep->pdev = pdev;
	fep->dev_id = dev_id++;

	platform_set_drvdata(pdev, ndev);

	if ((of_machine_is_compatible("fsl,imx6q") ||
	     of_machine_is_compatible("fsl,imx6dl")) &&
	    !of_property_read_bool(np, "fsl,err006687-workaround-present"))
		fep->quirks |= FEC_QUIRK_ERR006687;

	if (of_get_property(np, "fsl,magic-packet", NULL))
		fep->wol_flag |= FEC_WOL_HAS_MAGIC_PACKET;

	phy_node = of_parse_phandle(np, "phy-handle", 0);
	if (!phy_node && of_phy_is_fixed_link(np)) {
		ret = of_phy_register_fixed_link(np);
		if (ret < 0) {
			dev_err(&pdev->dev,
				"broken fixed-link specification\n");
			goto failed_phy;
		}
		phy_node = of_node_get(np);
	}
	fep->phy_node = phy_node;

	ret = of_get_phy_mode(pdev->dev.of_node);
	if (ret < 0) {
		pdata = dev_get_platdata(&pdev->dev);
		if (pdata)
			fep->phy_interface = pdata->phy;
		else
			fep->phy_interface = PHY_INTERFACE_MODE_MII;
	} else {
		fep->phy_interface = ret;
	}

	fep->clk_ipg = devm_clk_get(&pdev->dev, "ipg");
	if (IS_ERR(fep->clk_ipg)) {
		ret = PTR_ERR(fep->clk_ipg);
		goto failed_clk;
	}

	fep->clk_ahb = devm_clk_get(&pdev->dev, "ahb");
	if (IS_ERR(fep->clk_ahb)) {
		ret = PTR_ERR(fep->clk_ahb);
		goto failed_clk;
	}

	fep->itr_clk_rate = clk_get_rate(fep->clk_ahb);

	/* enet_out is optional, depends on board */
	fep->clk_enet_out = devm_clk_get(&pdev->dev, "enet_out");
	if (IS_ERR(fep->clk_enet_out))
		fep->clk_enet_out = NULL;

	fep->ptp_clk_on = false;
	mutex_init(&fep->ptp_clk_mutex);

	/* clk_ref is optional, depends on board */
	fep->clk_ref = devm_clk_get(&pdev->dev, "enet_clk_ref");
	if (IS_ERR(fep->clk_ref))
		fep->clk_ref = NULL;

	fep->bufdesc_ex = fep->quirks & FEC_QUIRK_HAS_BUFDESC_EX;
	fep->clk_ptp = devm_clk_get(&pdev->dev, "ptp");
	if (IS_ERR(fep->clk_ptp)) {
		fep->clk_ptp = NULL;
		fep->bufdesc_ex = false;
	}

	ret = fec_enet_clk_enable(ndev, true);
	if (ret)
		goto failed_clk;

	ret = clk_prepare_enable(fep->clk_ipg);
	if (ret)
		goto failed_clk_ipg;
	ret = clk_prepare_enable(fep->clk_ahb);
	if (ret)
		goto failed_clk_ahb;

	fep->reg_phy = devm_regulator_get_optional(&pdev->dev, "phy");
	if (!IS_ERR(fep->reg_phy)) {
		ret = regulator_enable(fep->reg_phy);
		if (ret) {
			dev_err(&pdev->dev,
				"Failed to enable phy regulator: %d\n", ret);
			goto failed_regulator;
		}
	} else {
		if (PTR_ERR(fep->reg_phy) == -EPROBE_DEFER) {
			ret = -EPROBE_DEFER;
			goto failed_regulator;
		}
		fep->reg_phy = NULL;
	}

	pm_runtime_set_autosuspend_delay(&pdev->dev, FEC_MDIO_PM_TIMEOUT);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_runtime_get_noresume(&pdev->dev);
	pm_runtime_set_active(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

	ret = fec_reset_phy(pdev);
	if (ret)
		goto failed_reset;

	irq_cnt = fec_enet_get_irq_cnt(pdev);
	if (fep->bufdesc_ex)
		fec_ptp_init(pdev, irq_cnt);

	ret = fec_enet_init(ndev);
	if (ret)
		goto failed_init;

	for (i = 0; i < irq_cnt; i++) {
		snprintf(irq_name, sizeof(irq_name), "int%d", i);
		irq = platform_get_irq_byname_optional(pdev, irq_name);
		if (irq < 0)
			irq = platform_get_irq(pdev, i);
		if (irq < 0) {
			ret = irq;
			goto failed_irq;
		}
		ret = devm_request_irq(&pdev->dev, irq, fec_enet_interrupt,
				       0, pdev->name, ndev);
		if (ret)
			goto failed_irq;

		fep->irq[i] = irq;
	}

	init_completion(&fep->mdio_done);
	ret = fec_enet_mii_init(pdev);
	if (ret)
		goto failed_mii_init;

	/* Carrier starts down, phylib will bring it up */
	netif_carrier_off(ndev);
	fec_enet_clk_enable(ndev, false);
	pinctrl_pm_select_sleep_state(&pdev->dev);

	ret = register_netdev(ndev);
	if (ret)
		goto failed_register;

	device_init_wakeup(&ndev->dev, fep->wol_flag &
			   FEC_WOL_HAS_MAGIC_PACKET);

	if (fep->bufdesc_ex && fep->ptp_clock)
		netdev_info(ndev, "registered PHC device %d\n", fep->dev_id);

	fep->rx_copybreak = COPYBREAK_DEFAULT;
	INIT_WORK(&fep->tx_timeout_work, fec_enet_timeout_work);

	pm_runtime_mark_last_busy(&pdev->dev);
	pm_runtime_put_autosuspend(&pdev->dev);

	return 0;

failed_register:
	fec_enet_mii_remove(fep);
failed_mii_init:
failed_irq:
failed_init:
	fec_ptp_stop(pdev);
	if (fep->reg_phy)
		regulator_disable(fep->reg_phy);
failed_reset:
	pm_runtime_put_noidle(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
failed_regulator:
	clk_disable_unprepare(fep->clk_ahb);
failed_clk_ahb:
	clk_disable_unprepare(fep->clk_ipg);
failed_clk_ipg:
	fec_enet_clk_enable(ndev, false);
failed_clk:
	if (of_phy_is_fixed_link(np))
		of_phy_deregister_fixed_link(np);
	of_node_put(phy_node);
failed_phy:
	dev_id--;
failed_ioremap:
	free_netdev(ndev);

	return ret;
}