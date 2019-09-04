#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vsc73xx {TYPE_1__* ds; int /*<<< orphan*/ * addr; struct device* dev; scalar_t__ reset; int /*<<< orphan*/  lock; int /*<<< orphan*/  spi; } ;
struct device {int dummy; } ;
struct spi_device {int bits_per_word; int /*<<< orphan*/  mode; struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ops; struct vsc73xx* priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  SPI_MODE_0 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct vsc73xx* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int dsa_register_switch (TYPE_1__*) ; 
 TYPE_1__* dsa_switch_alloc (struct device*,int) ; 
 int /*<<< orphan*/  dsa_unregister_switch (TYPE_1__*) ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_dev_get (struct spi_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct vsc73xx*) ; 
 int spi_setup (struct spi_device*) ; 
 int vsc73xx_detect (struct vsc73xx*) ; 
 int /*<<< orphan*/  vsc73xx_ds_ops ; 
 int vsc73xx_gpio_probe (struct vsc73xx*) ; 

__attribute__((used)) static int vsc73xx_probe(struct spi_device *spi)
{
	struct device *dev = &spi->dev;
	struct vsc73xx *vsc;
	int ret;

	vsc = devm_kzalloc(dev, sizeof(*vsc), GFP_KERNEL);
	if (!vsc)
		return -ENOMEM;

	spi_set_drvdata(spi, vsc);
	vsc->spi = spi_dev_get(spi);
	vsc->dev = dev;
	mutex_init(&vsc->lock);

	/* Release reset, if any */
	vsc->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(vsc->reset)) {
		dev_err(dev, "failed to get RESET GPIO\n");
		return PTR_ERR(vsc->reset);
	}
	if (vsc->reset)
		/* Wait 20ms according to datasheet table 245 */
		msleep(20);

	spi->mode = SPI_MODE_0;
	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	if (ret < 0) {
		dev_err(dev, "spi setup failed.\n");
		return ret;
	}

	ret = vsc73xx_detect(vsc);
	if (ret) {
		dev_err(dev, "no chip found (%d)\n", ret);
		return -ENODEV;
	}

	eth_random_addr(vsc->addr);
	dev_info(vsc->dev,
		 "MAC for control frames: %02X:%02X:%02X:%02X:%02X:%02X\n",
		 vsc->addr[0], vsc->addr[1], vsc->addr[2],
		 vsc->addr[3], vsc->addr[4], vsc->addr[5]);

	/* The VSC7395 switch chips have 5+1 ports which means 5
	 * ordinary ports and a sixth CPU port facing the processor
	 * with an RGMII interface. These ports are numbered 0..4
	 * and 6, so they leave a "hole" in the port map for port 5,
	 * which is invalid.
	 *
	 * The VSC7398 has 8 ports, port 7 is again the CPU port.
	 *
	 * We allocate 8 ports and avoid access to the nonexistant
	 * ports.
	 */
	vsc->ds = dsa_switch_alloc(dev, 8);
	if (!vsc->ds)
		return -ENOMEM;
	vsc->ds->priv = vsc;

	vsc->ds->ops = &vsc73xx_ds_ops;
	ret = dsa_register_switch(vsc->ds);
	if (ret) {
		dev_err(dev, "unable to register switch (%d)\n", ret);
		return ret;
	}

	ret = vsc73xx_gpio_probe(vsc);
	if (ret) {
		dsa_unregister_switch(vsc->ds);
		return ret;
	}

	return 0;
}