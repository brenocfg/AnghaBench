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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct cyttsp4 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CYTTSP4_I2C_DATA_SIZE ; 
 int EIO ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int PTR_ERR_OR_ZERO (struct cyttsp4*) ; 
 int /*<<< orphan*/  cyttsp4_i2c_bus_ops ; 
 struct cyttsp4* cyttsp4_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cyttsp4_i2c_probe(struct i2c_client *client,
				      const struct i2c_device_id *id)
{
	struct cyttsp4 *ts;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "I2C functionality not Supported\n");
		return -EIO;
	}

	ts = cyttsp4_probe(&cyttsp4_i2c_bus_ops, &client->dev, client->irq,
			  CYTTSP4_I2C_DATA_SIZE);

	return PTR_ERR_OR_ZERO(ts);
}