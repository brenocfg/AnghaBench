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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct i2c_par {TYPE_1__ adapter; struct i2c_client* ara; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_handle_smbus_alert (struct i2c_client*) ; 

__attribute__((used)) static void i2c_parport_irq(void *data)
{
	struct i2c_par *adapter = data;
	struct i2c_client *ara = adapter->ara;

	if (ara) {
		dev_dbg(&ara->dev, "SMBus alert received\n");
		i2c_handle_smbus_alert(ara);
	} else
		dev_dbg(&adapter->adapter.dev,
			"SMBus alert received but no ARA client!\n");
}