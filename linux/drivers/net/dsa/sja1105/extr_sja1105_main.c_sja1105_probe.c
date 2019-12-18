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
struct device {int /*<<< orphan*/  of_node; } ;
struct spi_device {int bits_per_word; struct device dev; } ;
struct sja1105_tagger_data {int /*<<< orphan*/  meta_lock; int /*<<< orphan*/  rxtstamp_work; int /*<<< orphan*/  skb_rxtstamp_queue; } ;
struct sja1105_private {struct dsa_switch* ds; int /*<<< orphan*/  mgmt_lock; struct sja1105_port* ports; struct sja1105_tagger_data tagger_data; TYPE_2__* info; struct spi_device* spidev; int /*<<< orphan*/  reset_gpio; } ;
struct sja1105_port {struct sja1105_tagger_data* data; TYPE_1__* dp; } ;
struct dsa_switch {TYPE_1__* ports; struct sja1105_private* priv; int /*<<< orphan*/ * ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {struct sja1105_port* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int SJA1105_NUM_PORTS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct sja1105_private* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int dsa_register_switch (struct dsa_switch*) ; 
 struct dsa_switch* dsa_switch_alloc (struct device*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* of_device_get_match_data (struct device*) ; 
 int sja1105_check_device_id (struct sja1105_private*) ; 
 int /*<<< orphan*/  sja1105_hw_reset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sja1105_rxtstamp_work ; 
 int /*<<< orphan*/  sja1105_switch_ops ; 
 int /*<<< orphan*/  sja1105_tas_setup (struct dsa_switch*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct sja1105_private*) ; 
 int spi_setup (struct spi_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sja1105_probe(struct spi_device *spi)
{
	struct sja1105_tagger_data *tagger_data;
	struct device *dev = &spi->dev;
	struct sja1105_private *priv;
	struct dsa_switch *ds;
	int rc, i;

	if (!dev->of_node) {
		dev_err(dev, "No DTS bindings for SJA1105 driver\n");
		return -EINVAL;
	}

	priv = devm_kzalloc(dev, sizeof(struct sja1105_private), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	/* Configure the optional reset pin and bring up switch */
	priv->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(priv->reset_gpio))
		dev_dbg(dev, "reset-gpios not defined, ignoring\n");
	else
		sja1105_hw_reset(priv->reset_gpio, 1, 1);

	/* Populate our driver private structure (priv) based on
	 * the device tree node that was probed (spi)
	 */
	priv->spidev = spi;
	spi_set_drvdata(spi, priv);

	/* Configure the SPI bus */
	spi->bits_per_word = 8;
	rc = spi_setup(spi);
	if (rc < 0) {
		dev_err(dev, "Could not init SPI\n");
		return rc;
	}

	priv->info = of_device_get_match_data(dev);

	/* Detect hardware device */
	rc = sja1105_check_device_id(priv);
	if (rc < 0) {
		dev_err(dev, "Device ID check failed: %d\n", rc);
		return rc;
	}

	dev_info(dev, "Probed switch chip: %s\n", priv->info->name);

	ds = dsa_switch_alloc(dev, SJA1105_NUM_PORTS);
	if (!ds)
		return -ENOMEM;

	ds->ops = &sja1105_switch_ops;
	ds->priv = priv;
	priv->ds = ds;

	tagger_data = &priv->tagger_data;
	skb_queue_head_init(&tagger_data->skb_rxtstamp_queue);
	INIT_WORK(&tagger_data->rxtstamp_work, sja1105_rxtstamp_work);
	spin_lock_init(&tagger_data->meta_lock);

	/* Connections between dsa_port and sja1105_port */
	for (i = 0; i < SJA1105_NUM_PORTS; i++) {
		struct sja1105_port *sp = &priv->ports[i];

		ds->ports[i].priv = sp;
		sp->dp = &ds->ports[i];
		sp->data = tagger_data;
	}
	mutex_init(&priv->mgmt_lock);

	sja1105_tas_setup(ds);

	return dsa_register_switch(priv->ds);
}