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
struct vsc73xx {TYPE_1__* ds; int /*<<< orphan*/ * addr; struct device* dev; scalar_t__ reset; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ops; struct vsc73xx* priv; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 int dsa_register_switch (TYPE_1__*) ; 
 TYPE_1__* dsa_switch_alloc (struct device*,int) ; 
 int /*<<< orphan*/  dsa_unregister_switch (TYPE_1__*) ; 
 int /*<<< orphan*/  eth_random_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int vsc73xx_detect (struct vsc73xx*) ; 
 int /*<<< orphan*/  vsc73xx_ds_ops ; 
 int vsc73xx_gpio_probe (struct vsc73xx*) ; 

int vsc73xx_probe(struct vsc73xx *vsc)
{
	struct device *dev = vsc->dev;
	int ret;

	/* Release reset, if any */
	vsc->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(vsc->reset)) {
		dev_err(dev, "failed to get RESET GPIO\n");
		return PTR_ERR(vsc->reset);
	}
	if (vsc->reset)
		/* Wait 20ms according to datasheet table 245 */
		msleep(20);

	ret = vsc73xx_detect(vsc);
	if (ret == -EAGAIN) {
		dev_err(vsc->dev,
			"Chip seems to be out of control. Assert reset and try again.\n");
		gpiod_set_value_cansleep(vsc->reset, 1);
		/* Reset pulse should be 20ns minimum, according to datasheet
		 * table 245, so 10us should be fine
		 */
		usleep_range(10, 100);
		gpiod_set_value_cansleep(vsc->reset, 0);
		/* Wait 20ms according to datasheet table 245 */
		msleep(20);
		ret = vsc73xx_detect(vsc);
	}
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