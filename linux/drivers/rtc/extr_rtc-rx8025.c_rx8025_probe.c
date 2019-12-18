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
struct rx8025_data {TYPE_1__* rtc; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int max_user_freq; int uie_unsupported; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 int I2C_FUNC_SMBUS_I2C_BLOCK ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 struct rx8025_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct i2c_client*) ; 
 TYPE_1__* devm_rtc_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rx8025_data*) ; 
 int /*<<< orphan*/  rx8025_handle_irq ; 
 int rx8025_init_client (struct i2c_client*) ; 
 int /*<<< orphan*/  rx8025_rtc_ops ; 
 int rx8025_sysfs_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rx8025_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = client->adapter;
	struct rx8025_data *rx8025;
	int err = 0;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA
				     | I2C_FUNC_SMBUS_I2C_BLOCK)) {
		dev_err(&adapter->dev,
			"doesn't support required functionality\n");
		return -EIO;
	}

	rx8025 = devm_kzalloc(&client->dev, sizeof(*rx8025), GFP_KERNEL);
	if (!rx8025)
		return -ENOMEM;

	rx8025->client = client;
	i2c_set_clientdata(client, rx8025);

	err = rx8025_init_client(client);
	if (err)
		return err;

	rx8025->rtc = devm_rtc_device_register(&client->dev, client->name,
					  &rx8025_rtc_ops, THIS_MODULE);
	if (IS_ERR(rx8025->rtc)) {
		dev_err(&client->dev, "unable to register the class device\n");
		return PTR_ERR(rx8025->rtc);
	}

	if (client->irq > 0) {
		dev_info(&client->dev, "IRQ %d supplied\n", client->irq);
		err = devm_request_threaded_irq(&client->dev, client->irq, NULL,
						rx8025_handle_irq,
						IRQF_ONESHOT,
						"rx8025", client);
		if (err) {
			dev_err(&client->dev, "unable to request IRQ, alarms disabled\n");
			client->irq = 0;
		}
	}

	rx8025->rtc->max_user_freq = 1;

	/* the rx8025 alarm only supports a minute accuracy */
	rx8025->rtc->uie_unsupported = 1;

	err = rx8025_sysfs_register(&client->dev);
	return err;
}