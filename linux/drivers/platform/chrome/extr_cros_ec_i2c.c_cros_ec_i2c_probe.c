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
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {TYPE_1__* adapter; int /*<<< orphan*/  irq; struct device dev; } ;
struct ec_response_get_protocol_info {int dummy; } ;
struct ec_host_response_i2c {int dummy; } ;
struct ec_host_request_i2c {int dummy; } ;
struct cros_ec_device {int din_size; int dout_size; int /*<<< orphan*/  phys_name; int /*<<< orphan*/  pkt_xfer; int /*<<< orphan*/  cmd_xfer; int /*<<< orphan*/  irq; struct i2c_client* priv; struct device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cros_ec_cmd_xfer_i2c ; 
 int /*<<< orphan*/  cros_ec_pkt_xfer_i2c ; 
 int cros_ec_register (struct cros_ec_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct cros_ec_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct cros_ec_device*) ; 

__attribute__((used)) static int cros_ec_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *dev_id)
{
	struct device *dev = &client->dev;
	struct cros_ec_device *ec_dev = NULL;
	int err;

	ec_dev = devm_kzalloc(dev, sizeof(*ec_dev), GFP_KERNEL);
	if (!ec_dev)
		return -ENOMEM;

	i2c_set_clientdata(client, ec_dev);
	ec_dev->dev = dev;
	ec_dev->priv = client;
	ec_dev->irq = client->irq;
	ec_dev->cmd_xfer = cros_ec_cmd_xfer_i2c;
	ec_dev->pkt_xfer = cros_ec_pkt_xfer_i2c;
	ec_dev->phys_name = client->adapter->name;
	ec_dev->din_size = sizeof(struct ec_host_response_i2c) +
			   sizeof(struct ec_response_get_protocol_info);
	ec_dev->dout_size = sizeof(struct ec_host_request_i2c);

	err = cros_ec_register(ec_dev);
	if (err) {
		dev_err(dev, "cannot register EC\n");
		return err;
	}

	return 0;
}