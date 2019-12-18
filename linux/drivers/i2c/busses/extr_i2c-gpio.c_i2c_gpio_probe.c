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
struct device {struct device_node* of_node; } ;
struct platform_device {int id; struct device dev; } ;
struct i2c_gpio_platform_data {int udelay; int timeout; scalar_t__ scl_is_output_only; scalar_t__ scl_is_open_drain; scalar_t__ sda_is_open_drain; } ;
struct i2c_algo_bit_data {int can_do_atomic; int udelay; int timeout; struct i2c_gpio_private_data* data; int /*<<< orphan*/  getsda; int /*<<< orphan*/  getscl; int /*<<< orphan*/  setscl; int /*<<< orphan*/  setsda; } ;
struct TYPE_2__ {struct device_node* of_node; struct device* parent; } ;
struct i2c_adapter {int class; int nr; TYPE_1__ dev; struct i2c_algo_bit_data* algo_data; int /*<<< orphan*/  name; int /*<<< orphan*/  owner; } ;
struct i2c_gpio_private_data {void* scl; void* sda; struct i2c_gpio_platform_data pdata; struct i2c_algo_bit_data bit_data; struct i2c_adapter adap; } ;
struct device_node {int dummy; } ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPIOD_OUT_HIGH ; 
 int GPIOD_OUT_HIGH_OPEN_DRAIN ; 
 int HZ ; 
 int I2C_CLASS_HWMON ; 
 int I2C_CLASS_SPD ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  desc_to_gpio (void*) ; 
 scalar_t__ dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct i2c_gpio_private_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gpiod_cansleep (void*) ; 
 int i2c_bit_add_numbered_bus (struct i2c_adapter*) ; 
 int /*<<< orphan*/  i2c_gpio_fault_injector_init (struct platform_device*) ; 
 void* i2c_gpio_get_desc (struct device*,char*,int,int) ; 
 int /*<<< orphan*/  i2c_gpio_getscl ; 
 int /*<<< orphan*/  i2c_gpio_getsda ; 
 int /*<<< orphan*/  i2c_gpio_setscl_val ; 
 int /*<<< orphan*/  i2c_gpio_setsda_val ; 
 int /*<<< orphan*/  memcpy (struct i2c_gpio_platform_data*,scalar_t__,int) ; 
 int /*<<< orphan*/  of_i2c_gpio_get_props (struct device_node*,struct i2c_gpio_platform_data*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct i2c_gpio_private_data*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int i2c_gpio_probe(struct platform_device *pdev)
{
	struct i2c_gpio_private_data *priv;
	struct i2c_gpio_platform_data *pdata;
	struct i2c_algo_bit_data *bit_data;
	struct i2c_adapter *adap;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	enum gpiod_flags gflags;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	adap = &priv->adap;
	bit_data = &priv->bit_data;
	pdata = &priv->pdata;

	if (np) {
		of_i2c_gpio_get_props(np, pdata);
	} else {
		/*
		 * If all platform data settings are zero it is OK
		 * to not provide any platform data from the board.
		 */
		if (dev_get_platdata(dev))
			memcpy(pdata, dev_get_platdata(dev), sizeof(*pdata));
	}

	/*
	 * First get the GPIO pins; if it fails, we'll defer the probe.
	 * If the SCL/SDA lines are marked "open drain" by platform data or
	 * device tree then this means that something outside of our control is
	 * marking these lines to be handled as open drain, and we should just
	 * handle them as we handle any other output. Else we enforce open
	 * drain as this is required for an I2C bus.
	 */
	if (pdata->sda_is_open_drain)
		gflags = GPIOD_OUT_HIGH;
	else
		gflags = GPIOD_OUT_HIGH_OPEN_DRAIN;
	priv->sda = i2c_gpio_get_desc(dev, "sda", 0, gflags);
	if (IS_ERR(priv->sda))
		return PTR_ERR(priv->sda);

	if (pdata->scl_is_open_drain)
		gflags = GPIOD_OUT_HIGH;
	else
		gflags = GPIOD_OUT_HIGH_OPEN_DRAIN;
	priv->scl = i2c_gpio_get_desc(dev, "scl", 1, gflags);
	if (IS_ERR(priv->scl))
		return PTR_ERR(priv->scl);

	if (gpiod_cansleep(priv->sda) || gpiod_cansleep(priv->scl))
		dev_warn(dev, "Slow GPIO pins might wreak havoc into I2C/SMBus bus timing");
	else
		bit_data->can_do_atomic = true;

	bit_data->setsda = i2c_gpio_setsda_val;
	bit_data->setscl = i2c_gpio_setscl_val;

	if (!pdata->scl_is_output_only)
		bit_data->getscl = i2c_gpio_getscl;
	bit_data->getsda = i2c_gpio_getsda;

	if (pdata->udelay)
		bit_data->udelay = pdata->udelay;
	else if (pdata->scl_is_output_only)
		bit_data->udelay = 50;			/* 10 kHz */
	else
		bit_data->udelay = 5;			/* 100 kHz */

	if (pdata->timeout)
		bit_data->timeout = pdata->timeout;
	else
		bit_data->timeout = HZ / 10;		/* 100 ms */

	bit_data->data = priv;

	adap->owner = THIS_MODULE;
	if (np)
		strlcpy(adap->name, dev_name(dev), sizeof(adap->name));
	else
		snprintf(adap->name, sizeof(adap->name), "i2c-gpio%d", pdev->id);

	adap->algo_data = bit_data;
	adap->class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	adap->dev.parent = dev;
	adap->dev.of_node = np;

	adap->nr = pdev->id;
	ret = i2c_bit_add_numbered_bus(adap);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, priv);

	/*
	 * FIXME: using global GPIO numbers is not helpful. If/when we
	 * get accessors to get the actual name of the GPIO line,
	 * from the descriptor, then provide that instead.
	 */
	dev_info(dev, "using lines %u (SDA) and %u (SCL%s)\n",
		 desc_to_gpio(priv->sda), desc_to_gpio(priv->scl),
		 pdata->scl_is_output_only
		 ? ", no clock stretching" : "");

	i2c_gpio_fault_injector_init(pdev);

	return 0;
}