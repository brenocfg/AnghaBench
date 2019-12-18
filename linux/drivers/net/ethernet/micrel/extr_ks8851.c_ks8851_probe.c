#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct spi_device {int bits_per_word; TYPE_3__ dev; int /*<<< orphan*/  irq; } ;
struct net_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  if_port; int /*<<< orphan*/ * ethtool_ops; } ;
struct TYPE_9__ {int phy_id; int phy_id_mask; int reg_num_mask; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; struct net_device* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  register_write; int /*<<< orphan*/  register_read; int /*<<< orphan*/  width; struct ks8851_net* data; } ;
struct ks8851_net {int tx_space; int gpio; int rc_ccr; void* vdd_io; void* vdd_reg; struct net_device* netdev; int /*<<< orphan*/  txq; int /*<<< orphan*/  msg_enable; TYPE_2__ mii; TYPE_1__ eeprom; int /*<<< orphan*/  spi_msg2; int /*<<< orphan*/ * spi_xfer2; int /*<<< orphan*/  spi_msg1; int /*<<< orphan*/  spi_xfer1; int /*<<< orphan*/  rxctrl_work; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  statelock; int /*<<< orphan*/  lock; struct spi_device* spidev; } ;

/* Variables and functions */
 int CCR_EEPROM ; 
 unsigned int CIDER_ID ; 
 int /*<<< orphan*/  CIDER_REV_GET (unsigned int) ; 
 unsigned int CIDER_REV_MASK ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOF_OUT_INIT_LOW ; 
 int /*<<< orphan*/  GRR_GSR ; 
 int /*<<< orphan*/  IF_PORT_100BASET ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  KS_CCR ; 
 int /*<<< orphan*/  KS_CIDER ; 
 int NETIF_MSG_DRV ; 
 int NETIF_MSG_LINK ; 
 int NETIF_MSG_PROBE ; 
 int /*<<< orphan*/  PCI_EEPROM_WIDTH_93C46 ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_3__*) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int devm_gpio_request_one (TYPE_3__*,int,int /*<<< orphan*/ ,char*) ; 
 void* devm_regulator_get (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 scalar_t__ gpio_is_valid (int) ; 
 int /*<<< orphan*/  gpio_set_value (int,int) ; 
 int /*<<< orphan*/  ks8851_eeprom_regread ; 
 int /*<<< orphan*/  ks8851_eeprom_regwrite ; 
 int /*<<< orphan*/  ks8851_ethtool_ops ; 
 int /*<<< orphan*/  ks8851_init_mac (struct ks8851_net*) ; 
 int /*<<< orphan*/  ks8851_netdev_ops ; 
 int /*<<< orphan*/  ks8851_phy_read ; 
 int /*<<< orphan*/  ks8851_phy_write ; 
 void* ks8851_rdreg16 (struct ks8851_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks8851_read_selftest (struct ks8851_net*) ; 
 int /*<<< orphan*/  ks8851_rxctrl_work ; 
 int /*<<< orphan*/  ks8851_soft_reset (struct ks8851_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks8851_tx_work ; 
 int /*<<< orphan*/  msg_enable ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct ks8851_net* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_msg_init (int /*<<< orphan*/ ,int) ; 
 int of_get_named_gpio_flags (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  regulator_disable (void*) ; 
 int regulator_enable (void*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct ks8851_net*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ks8851_probe(struct spi_device *spi)
{
	struct net_device *ndev;
	struct ks8851_net *ks;
	int ret;
	unsigned cider;
	int gpio;

	ndev = alloc_etherdev(sizeof(struct ks8851_net));
	if (!ndev)
		return -ENOMEM;

	spi->bits_per_word = 8;

	ks = netdev_priv(ndev);

	ks->netdev = ndev;
	ks->spidev = spi;
	ks->tx_space = 6144;

	gpio = of_get_named_gpio_flags(spi->dev.of_node, "reset-gpios",
				       0, NULL);
	if (gpio == -EPROBE_DEFER) {
		ret = gpio;
		goto err_gpio;
	}

	ks->gpio = gpio;
	if (gpio_is_valid(gpio)) {
		ret = devm_gpio_request_one(&spi->dev, gpio,
					    GPIOF_OUT_INIT_LOW, "ks8851_rst_n");
		if (ret) {
			dev_err(&spi->dev, "reset gpio request failed\n");
			goto err_gpio;
		}
	}

	ks->vdd_io = devm_regulator_get(&spi->dev, "vdd-io");
	if (IS_ERR(ks->vdd_io)) {
		ret = PTR_ERR(ks->vdd_io);
		goto err_reg_io;
	}

	ret = regulator_enable(ks->vdd_io);
	if (ret) {
		dev_err(&spi->dev, "regulator vdd_io enable fail: %d\n",
			ret);
		goto err_reg_io;
	}

	ks->vdd_reg = devm_regulator_get(&spi->dev, "vdd");
	if (IS_ERR(ks->vdd_reg)) {
		ret = PTR_ERR(ks->vdd_reg);
		goto err_reg;
	}

	ret = regulator_enable(ks->vdd_reg);
	if (ret) {
		dev_err(&spi->dev, "regulator vdd enable fail: %d\n",
			ret);
		goto err_reg;
	}

	if (gpio_is_valid(gpio)) {
		usleep_range(10000, 11000);
		gpio_set_value(gpio, 1);
	}

	mutex_init(&ks->lock);
	spin_lock_init(&ks->statelock);

	INIT_WORK(&ks->tx_work, ks8851_tx_work);
	INIT_WORK(&ks->rxctrl_work, ks8851_rxctrl_work);

	/* initialise pre-made spi transfer messages */

	spi_message_init(&ks->spi_msg1);
	spi_message_add_tail(&ks->spi_xfer1, &ks->spi_msg1);

	spi_message_init(&ks->spi_msg2);
	spi_message_add_tail(&ks->spi_xfer2[0], &ks->spi_msg2);
	spi_message_add_tail(&ks->spi_xfer2[1], &ks->spi_msg2);

	/* setup EEPROM state */

	ks->eeprom.data = ks;
	ks->eeprom.width = PCI_EEPROM_WIDTH_93C46;
	ks->eeprom.register_read = ks8851_eeprom_regread;
	ks->eeprom.register_write = ks8851_eeprom_regwrite;

	/* setup mii state */
	ks->mii.dev		= ndev;
	ks->mii.phy_id		= 1,
	ks->mii.phy_id_mask	= 1;
	ks->mii.reg_num_mask	= 0xf;
	ks->mii.mdio_read	= ks8851_phy_read;
	ks->mii.mdio_write	= ks8851_phy_write;

	dev_info(&spi->dev, "message enable is %d\n", msg_enable);

	/* set the default message enable */
	ks->msg_enable = netif_msg_init(msg_enable, (NETIF_MSG_DRV |
						     NETIF_MSG_PROBE |
						     NETIF_MSG_LINK));

	skb_queue_head_init(&ks->txq);

	ndev->ethtool_ops = &ks8851_ethtool_ops;
	SET_NETDEV_DEV(ndev, &spi->dev);

	spi_set_drvdata(spi, ks);

	netif_carrier_off(ks->netdev);
	ndev->if_port = IF_PORT_100BASET;
	ndev->netdev_ops = &ks8851_netdev_ops;
	ndev->irq = spi->irq;

	/* issue a global soft reset to reset the device. */
	ks8851_soft_reset(ks, GRR_GSR);

	/* simple check for a valid chip being connected to the bus */
	cider = ks8851_rdreg16(ks, KS_CIDER);
	if ((cider & ~CIDER_REV_MASK) != CIDER_ID) {
		dev_err(&spi->dev, "failed to read device ID\n");
		ret = -ENODEV;
		goto err_id;
	}

	/* cache the contents of the CCR register for EEPROM, etc. */
	ks->rc_ccr = ks8851_rdreg16(ks, KS_CCR);

	ks8851_read_selftest(ks);
	ks8851_init_mac(ks);

	ret = register_netdev(ndev);
	if (ret) {
		dev_err(&spi->dev, "failed to register network device\n");
		goto err_netdev;
	}

	netdev_info(ndev, "revision %d, MAC %pM, IRQ %d, %s EEPROM\n",
		    CIDER_REV_GET(cider), ndev->dev_addr, ndev->irq,
		    ks->rc_ccr & CCR_EEPROM ? "has" : "no");

	return 0;

err_netdev:
err_id:
	if (gpio_is_valid(gpio))
		gpio_set_value(gpio, 0);
	regulator_disable(ks->vdd_reg);
err_reg:
	regulator_disable(ks->vdd_io);
err_reg_io:
err_gpio:
	free_netdev(ndev);
	return ret;
}