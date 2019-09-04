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
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;
struct elan_tp_data {int in_fw_update; TYPE_1__* ops; struct i2c_client* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* iap_reset ) (struct i2c_client*) ;} ;

/* Variables and functions */
 int __elan_update_firmware (struct elan_tp_data*,struct firmware const*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elan_initialize (struct elan_tp_data*) ; 
 int /*<<< orphan*/  elan_query_device_info (struct elan_tp_data*) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct i2c_client*) ; 

__attribute__((used)) static int elan_update_firmware(struct elan_tp_data *data,
				const struct firmware *fw)
{
	struct i2c_client *client = data->client;
	int retval;

	dev_dbg(&client->dev, "Starting firmware update....\n");

	disable_irq(client->irq);
	data->in_fw_update = true;

	retval = __elan_update_firmware(data, fw);
	if (retval) {
		dev_err(&client->dev, "firmware update failed: %d\n", retval);
		data->ops->iap_reset(client);
	} else {
		/* Reinitialize TP after fw is updated */
		elan_initialize(data);
		elan_query_device_info(data);
	}

	data->in_fw_update = false;
	enable_irq(client->irq);

	return retval;
}