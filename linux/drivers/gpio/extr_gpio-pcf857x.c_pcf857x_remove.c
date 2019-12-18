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
struct pcf857x_platform_data {int (* teardown ) (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  context; } ;
struct TYPE_2__ {int /*<<< orphan*/  ngpio; int /*<<< orphan*/  base; } ;
struct pcf857x {TYPE_1__ chip; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,int) ; 
 struct pcf857x_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct pcf857x* i2c_get_clientdata (struct i2c_client*) ; 
 int stub1 (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcf857x_remove(struct i2c_client *client)
{
	struct pcf857x_platform_data	*pdata = dev_get_platdata(&client->dev);
	struct pcf857x			*gpio = i2c_get_clientdata(client);
	int				status = 0;

	if (pdata && pdata->teardown) {
		status = pdata->teardown(client,
				gpio->chip.base, gpio->chip.ngpio,
				pdata->context);
		if (status < 0) {
			dev_err(&client->dev, "%s --> %d\n",
					"teardown", status);
			return status;
		}
	}

	return status;
}