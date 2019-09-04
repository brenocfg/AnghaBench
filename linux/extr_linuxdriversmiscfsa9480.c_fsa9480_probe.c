#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; TYPE_1__* platform_data; int /*<<< orphan*/  parent; } ;
struct i2c_client {scalar_t__ irq; TYPE_2__ dev; } ;
struct i2c_adapter {int dummy; } ;
struct fsa9480_usbsw {TYPE_1__* pdata; struct i2c_client* client; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* reset_cb ) () ;} ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FSA9480_REG_TIMING1 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  INT_ATTACH ; 
 struct fsa9480_usbsw* chip ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct fsa9480_usbsw*) ; 
 int /*<<< orphan*/  fsa9480_detect_dev (struct fsa9480_usbsw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsa9480_group ; 
 int fsa9480_irq_init (struct fsa9480_usbsw*) ; 
 int /*<<< orphan*/  fsa9480_write_reg (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct fsa9480_usbsw*) ; 
 int /*<<< orphan*/  kfree (struct fsa9480_usbsw*) ; 
 struct fsa9480_usbsw* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct i2c_adapter* to_i2c_adapter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsa9480_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	struct fsa9480_usbsw *usbsw;
	int ret = 0;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	usbsw = kzalloc(sizeof(struct fsa9480_usbsw), GFP_KERNEL);
	if (!usbsw) {
		dev_err(&client->dev, "failed to allocate driver data\n");
		return -ENOMEM;
	}

	usbsw->client = client;
	usbsw->pdata = client->dev.platform_data;

	chip = usbsw;

	i2c_set_clientdata(client, usbsw);

	ret = fsa9480_irq_init(usbsw);
	if (ret)
		goto fail1;

	ret = sysfs_create_group(&client->dev.kobj, &fsa9480_group);
	if (ret) {
		dev_err(&client->dev,
				"failed to create fsa9480 attribute group\n");
		goto fail2;
	}

	/* ADC Detect Time: 500ms */
	fsa9480_write_reg(client, FSA9480_REG_TIMING1, 0x6);

	if (chip->pdata->reset_cb)
		chip->pdata->reset_cb();

	/* device detection */
	fsa9480_detect_dev(usbsw, INT_ATTACH);

	pm_runtime_set_active(&client->dev);

	return 0;

fail2:
	if (client->irq)
		free_irq(client->irq, usbsw);
fail1:
	kfree(usbsw);
	return ret;
}