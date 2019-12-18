#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pcf8523 {int /*<<< orphan*/  rtc; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 struct pcf8523* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_rtc_device_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pcf8523*) ; 
 int pcf8523_load_capacitance (struct i2c_client*) ; 
 int /*<<< orphan*/  pcf8523_rtc_ops ; 
 int pcf8523_set_pm (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcf8523_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct pcf8523 *pcf;
	int err;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		return -ENODEV;

	pcf = devm_kzalloc(&client->dev, sizeof(*pcf), GFP_KERNEL);
	if (!pcf)
		return -ENOMEM;

	err = pcf8523_load_capacitance(client);
	if (err < 0)
		dev_warn(&client->dev, "failed to set xtal load capacitance: %d",
			 err);

	err = pcf8523_set_pm(client, 0);
	if (err < 0)
		return err;

	pcf->rtc = devm_rtc_device_register(&client->dev, DRIVER_NAME,
				       &pcf8523_rtc_ops, THIS_MODULE);
	if (IS_ERR(pcf->rtc))
		return PTR_ERR(pcf->rtc);

	i2c_set_clientdata(client, pcf);

	return 0;
}