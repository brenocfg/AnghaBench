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
struct s35390a {int twentyfourhour; struct i2c_client* rtc; struct i2c_client** client; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int uie_unsupported; scalar_t__ addr; int /*<<< orphan*/  adapter; struct device dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 scalar_t__ IS_ERR (struct i2c_client*) ; 
 int PTR_ERR (struct i2c_client*) ; 
 int /*<<< orphan*/  RTC_AF ; 
 int /*<<< orphan*/  S35390A_CMD_STATUS2 ; 
 char S35390A_FLAG_24H ; 
 char S35390A_FLAG_INT2 ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (struct device*,int) ; 
 struct i2c_client* devm_i2c_new_dummy_device (struct device*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct s35390a* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct i2c_client* devm_rtc_device_register (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct s35390a*) ; 
 int /*<<< orphan*/  rtc_update_irq (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int s35390a_disable_test_mode (struct s35390a*) ; 
 TYPE_2__ s35390a_driver ; 
 int s35390a_read_status (struct s35390a*,char*) ; 
 int /*<<< orphan*/  s35390a_rtc_ops ; 
 int s35390a_set_reg (struct s35390a*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int s35390a_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	int err, err_read;
	unsigned int i;
	struct s35390a *s35390a;
	char buf, status1;
	struct device *dev = &client->dev;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		return -ENODEV;

	s35390a = devm_kzalloc(dev, sizeof(struct s35390a), GFP_KERNEL);
	if (!s35390a)
		return -ENOMEM;

	s35390a->client[0] = client;
	i2c_set_clientdata(client, s35390a);

	/* This chip uses multiple addresses, use dummy devices for them */
	for (i = 1; i < 8; ++i) {
		s35390a->client[i] = devm_i2c_new_dummy_device(dev,
							       client->adapter,
							       client->addr + i);
		if (IS_ERR(s35390a->client[i])) {
			dev_err(dev, "Address %02x unavailable\n",
				client->addr + i);
			return PTR_ERR(s35390a->client[i]);
		}
	}

	err_read = s35390a_read_status(s35390a, &status1);
	if (err_read < 0) {
		dev_err(dev, "error resetting chip\n");
		return err_read;
	}

	if (status1 & S35390A_FLAG_24H)
		s35390a->twentyfourhour = 1;
	else
		s35390a->twentyfourhour = 0;

	if (status1 & S35390A_FLAG_INT2) {
		/* disable alarm (and maybe test mode) */
		buf = 0;
		err = s35390a_set_reg(s35390a, S35390A_CMD_STATUS2, &buf, 1);
		if (err < 0) {
			dev_err(dev, "error disabling alarm");
			return err;
		}
	} else {
		err = s35390a_disable_test_mode(s35390a);
		if (err < 0) {
			dev_err(dev, "error disabling test mode\n");
			return err;
		}
	}

	device_set_wakeup_capable(dev, 1);

	s35390a->rtc = devm_rtc_device_register(dev, s35390a_driver.driver.name,
						&s35390a_rtc_ops, THIS_MODULE);

	if (IS_ERR(s35390a->rtc))
		return PTR_ERR(s35390a->rtc);

	/* supports per-minute alarms only, therefore set uie_unsupported */
	s35390a->rtc->uie_unsupported = 1;

	if (status1 & S35390A_FLAG_INT2)
		rtc_update_irq(s35390a->rtc, 1, RTC_AF);

	return 0;
}