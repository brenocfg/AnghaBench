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
struct rmi_device_platform_data {int irq; } ;
struct TYPE_2__ {char* proto_name; int /*<<< orphan*/ * ops; struct rmi_device_platform_data pdata; int /*<<< orphan*/ * dev; } ;
struct rmi_smb_xport {TYPE_1__ xport; int /*<<< orphan*/  mappingtable_mutex; int /*<<< orphan*/  page_mutex; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_HOST_NOTIFY ; 
 int I2C_FUNC_SMBUS_READ_BLOCK_DATA ; 
 int /*<<< orphan*/  RMI_DEBUG_XPORT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct rmi_device_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int dev_name (int /*<<< orphan*/ *) ; 
 struct rmi_smb_xport* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct rmi_smb_xport*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmi_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int rmi_register_transport_device (TYPE_1__*) ; 
 int rmi_smb_get_version (struct rmi_smb_xport*) ; 
 int /*<<< orphan*/  rmi_smb_ops ; 

__attribute__((used)) static int rmi_smb_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct rmi_device_platform_data *pdata = dev_get_platdata(&client->dev);
	struct rmi_smb_xport *rmi_smb;
	int smbus_version;
	int error;

	if (!pdata) {
		dev_err(&client->dev, "no platform data, aborting\n");
		return -ENOMEM;
	}

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BLOCK_DATA |
				     I2C_FUNC_SMBUS_HOST_NOTIFY)) {
		dev_err(&client->dev,
			"adapter does not support required functionality\n");
		return -ENODEV;
	}

	if (client->irq <= 0) {
		dev_err(&client->dev, "no IRQ provided, giving up\n");
		return client->irq ? client->irq : -ENODEV;
	}

	rmi_smb = devm_kzalloc(&client->dev, sizeof(struct rmi_smb_xport),
				GFP_KERNEL);
	if (!rmi_smb)
		return -ENOMEM;

	rmi_dbg(RMI_DEBUG_XPORT, &client->dev, "Probing %s\n",
		dev_name(&client->dev));

	rmi_smb->client = client;
	mutex_init(&rmi_smb->page_mutex);
	mutex_init(&rmi_smb->mappingtable_mutex);

	rmi_smb->xport.dev = &client->dev;
	rmi_smb->xport.pdata = *pdata;
	rmi_smb->xport.pdata.irq = client->irq;
	rmi_smb->xport.proto_name = "smb";
	rmi_smb->xport.ops = &rmi_smb_ops;

	smbus_version = rmi_smb_get_version(rmi_smb);
	if (smbus_version < 0)
		return smbus_version;

	rmi_dbg(RMI_DEBUG_XPORT, &client->dev, "Smbus version is %d",
		smbus_version);

	if (smbus_version != 2 && smbus_version != 3) {
		dev_err(&client->dev, "Unrecognized SMB version %d\n",
				smbus_version);
		return -ENODEV;
	}

	i2c_set_clientdata(client, rmi_smb);

	dev_info(&client->dev, "registering SMbus-connected sensor\n");

	error = rmi_register_transport_device(&rmi_smb->xport);
	if (error) {
		dev_err(&client->dev, "failed to register sensor: %d\n", error);
		return error;
	}

	return 0;
}