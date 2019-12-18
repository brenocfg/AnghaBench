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
struct TYPE_5__ {struct ca8210_platform_data* platform_data; } ;
struct spi_device {TYPE_2__ dev; } ;
struct ieee802154_hw {TYPE_1__* phy; TYPE_2__* parent; struct ca8210_priv* priv; } ;
struct ca8210_priv {int async_tx_pending; int hw_registered; int promiscuous; struct spi_device* spi; int /*<<< orphan*/  sync_exchange_complete; int /*<<< orphan*/  spi_transfer_complete; int /*<<< orphan*/  ca8210_is_awake; scalar_t__ retries; scalar_t__ sync_down; scalar_t__ sync_up; int /*<<< orphan*/  lock; struct ieee802154_hw* hw; } ;
struct ca8210_platform_data {scalar_t__ extclockenable; } ;
struct TYPE_4__ {int /*<<< orphan*/  perm_extended_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_IEEE802154_CA8210_DEBUGFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int ca8210_config_extern_clk (struct ca8210_platform_data*,struct spi_device*,int) ; 
 int ca8210_dev_com_init (struct ca8210_priv*) ; 
 int ca8210_get_platform_data (struct spi_device*,struct ca8210_platform_data*) ; 
 int /*<<< orphan*/  ca8210_hw_setup (struct ieee802154_hw*) ; 
 int ca8210_interrupt_init (struct spi_device*) ; 
 int /*<<< orphan*/  ca8210_phy_ops ; 
 int ca8210_register_ext_clock (struct spi_device*) ; 
 int /*<<< orphan*/  ca8210_remove (struct spi_device*) ; 
 int ca8210_reset_init (struct spi_device*) ; 
 int /*<<< orphan*/  ca8210_reset_send (struct spi_device*,int) ; 
 int /*<<< orphan*/ * ca8210_test_int_driver_write ; 
 int /*<<< orphan*/  ca8210_test_interface_init (struct ca8210_priv*) ; 
 int /*<<< orphan*/ * cascoda_api_upstream ; 
 int /*<<< orphan*/  dev_crit (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 struct ieee802154_hw* ieee802154_alloc_hw (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee802154_random_extended_addr (int /*<<< orphan*/ *) ; 
 int ieee802154_register_hw (struct ieee802154_hw*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct ca8210_platform_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int link_to_linux_err (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct ca8210_priv*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int tdme_chipinit (struct spi_device*) ; 

__attribute__((used)) static int ca8210_probe(struct spi_device *spi_device)
{
	struct ca8210_priv *priv;
	struct ieee802154_hw *hw;
	struct ca8210_platform_data *pdata;
	int ret;

	dev_info(&spi_device->dev, "Inserting ca8210\n");

	/* allocate ieee802154_hw and private data */
	hw = ieee802154_alloc_hw(sizeof(struct ca8210_priv), &ca8210_phy_ops);
	if (!hw) {
		dev_crit(&spi_device->dev, "ieee802154_alloc_hw failed\n");
		ret = -ENOMEM;
		goto error;
	}

	priv = hw->priv;
	priv->hw = hw;
	priv->spi = spi_device;
	hw->parent = &spi_device->dev;
	spin_lock_init(&priv->lock);
	priv->async_tx_pending = false;
	priv->hw_registered = false;
	priv->sync_up = 0;
	priv->sync_down = 0;
	priv->promiscuous = false;
	priv->retries = 0;
	init_completion(&priv->ca8210_is_awake);
	init_completion(&priv->spi_transfer_complete);
	init_completion(&priv->sync_exchange_complete);
	spi_set_drvdata(priv->spi, priv);
	if (IS_ENABLED(CONFIG_IEEE802154_CA8210_DEBUGFS)) {
		cascoda_api_upstream = ca8210_test_int_driver_write;
		ca8210_test_interface_init(priv);
	} else {
		cascoda_api_upstream = NULL;
	}
	ca8210_hw_setup(hw);
	ieee802154_random_extended_addr(&hw->phy->perm_extended_addr);

	pdata = kmalloc(sizeof(*pdata), GFP_KERNEL);
	if (!pdata) {
		ret = -ENOMEM;
		goto error;
	}

	priv->spi->dev.platform_data = pdata;
	ret = ca8210_get_platform_data(priv->spi, pdata);
	if (ret) {
		dev_crit(&spi_device->dev, "ca8210_get_platform_data failed\n");
		goto error;
	}

	ret = ca8210_dev_com_init(priv);
	if (ret) {
		dev_crit(&spi_device->dev, "ca8210_dev_com_init failed\n");
		goto error;
	}
	ret = ca8210_reset_init(priv->spi);
	if (ret) {
		dev_crit(&spi_device->dev, "ca8210_reset_init failed\n");
		goto error;
	}

	ret = ca8210_interrupt_init(priv->spi);
	if (ret) {
		dev_crit(&spi_device->dev, "ca8210_interrupt_init failed\n");
		goto error;
	}

	msleep(100);

	ca8210_reset_send(priv->spi, 1);

	ret = tdme_chipinit(priv->spi);
	if (ret) {
		dev_crit(&spi_device->dev, "tdme_chipinit failed\n");
		goto error;
	}

	if (pdata->extclockenable) {
		ret = ca8210_config_extern_clk(pdata, priv->spi, 1);
		if (ret) {
			dev_crit(
				&spi_device->dev,
				"ca8210_config_extern_clk failed\n"
			);
			goto error;
		}
		ret = ca8210_register_ext_clock(priv->spi);
		if (ret) {
			dev_crit(
				&spi_device->dev,
				"ca8210_register_ext_clock failed\n"
			);
			goto error;
		}
	}

	ret = ieee802154_register_hw(hw);
	if (ret) {
		dev_crit(&spi_device->dev, "ieee802154_register_hw failed\n");
		goto error;
	}
	priv->hw_registered = true;

	return 0;
error:
	msleep(100); /* wait for pending spi transfers to complete */
	ca8210_remove(spi_device);
	return link_to_linux_err(ret);
}