#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int i2c_write_max; struct dvb_frontend* dvb_frontend; } ;
struct TYPE_12__ {int /*<<< orphan*/  reg_write; int /*<<< orphan*/  reg_read; struct dvb_usb_device* reg_priv; } ;
struct zd1301_dev {struct i2c_client* i2c_client_tuner; struct platform_device* platform_device_demod; TYPE_1__ mt2060_pdata; TYPE_6__ demod_pdata; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {TYPE_4__* driver; } ;
struct platform_device {TYPE_5__ dev; } ;
struct TYPE_9__ {TYPE_2__* driver; } ;
struct i2c_client {TYPE_3__ dev; } ;
struct i2c_board_info {int addr; TYPE_1__* platform_data; int /*<<< orphan*/  type; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {struct usb_interface* intf; } ;
struct dvb_usb_adapter {struct dvb_frontend** fe; } ;
struct dvb_frontend {int dummy; } ;
typedef  int /*<<< orphan*/  board_info ;
struct TYPE_10__ {int /*<<< orphan*/  owner; } ;
struct TYPE_8__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  I2C_NAME_SIZE ; 
 scalar_t__ IS_ERR (struct platform_device*) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int PTR_ERR (struct platform_device*) ; 
 struct dvb_usb_device* adap_to_d (struct dvb_usb_adapter*) ; 
 struct zd1301_dev* adap_to_priv (struct dvb_usb_adapter*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct i2c_client* i2c_new_device (struct i2c_adapter*,struct i2c_board_info*) ; 
 int /*<<< orphan*/  i2c_unregister_device (struct i2c_client*) ; 
 int /*<<< orphan*/  memset (struct i2c_board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct platform_device* platform_device_register_data (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_6__*,int) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 
 int /*<<< orphan*/  request_module (char*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 struct dvb_frontend* zd1301_demod_get_dvb_frontend (struct platform_device*) ; 
 struct i2c_adapter* zd1301_demod_get_i2c_adapter (struct platform_device*) ; 
 int /*<<< orphan*/  zd1301_demod_rreg ; 
 int /*<<< orphan*/  zd1301_demod_wreg ; 

__attribute__((used)) static int zd1301_frontend_attach(struct dvb_usb_adapter *adap)
{
	struct dvb_usb_device *d = adap_to_d(adap);
	struct zd1301_dev *dev = adap_to_priv(adap);
	struct usb_interface *intf = d->intf;
	struct platform_device *pdev;
	struct i2c_client *client;
	struct i2c_board_info board_info;
	struct i2c_adapter *adapter;
	struct dvb_frontend *frontend;
	int ret;

	dev_dbg(&intf->dev, "\n");

	/* Add platform demod */
	dev->demod_pdata.reg_priv = d;
	dev->demod_pdata.reg_read = zd1301_demod_rreg;
	dev->demod_pdata.reg_write = zd1301_demod_wreg;
	request_module("%s", "zd1301_demod");
	pdev = platform_device_register_data(&intf->dev,
					     "zd1301_demod",
					     PLATFORM_DEVID_AUTO,
					     &dev->demod_pdata,
					     sizeof(dev->demod_pdata));
	if (IS_ERR(pdev)) {
		ret = PTR_ERR(pdev);
		goto err;
	}
	if (!pdev->dev.driver) {
		ret = -ENODEV;
		goto err;
	}
	if (!try_module_get(pdev->dev.driver->owner)) {
		ret = -ENODEV;
		goto err_platform_device_unregister;
	}

	adapter = zd1301_demod_get_i2c_adapter(pdev);
	frontend = zd1301_demod_get_dvb_frontend(pdev);
	if (!adapter || !frontend) {
		ret = -ENODEV;
		goto err_module_put_demod;
	}

	/* Add I2C tuner */
	dev->mt2060_pdata.i2c_write_max = 9;
	dev->mt2060_pdata.dvb_frontend = frontend;
	memset(&board_info, 0, sizeof(board_info));
	strscpy(board_info.type, "mt2060", I2C_NAME_SIZE);
	board_info.addr = 0x60;
	board_info.platform_data = &dev->mt2060_pdata;
	request_module("%s", "mt2060");
	client = i2c_new_device(adapter, &board_info);
	if (!client || !client->dev.driver) {
		ret = -ENODEV;
		goto err_module_put_demod;
	}
	if (!try_module_get(client->dev.driver->owner)) {
		ret = -ENODEV;
		goto err_i2c_unregister_device;
	}

	dev->platform_device_demod = pdev;
	dev->i2c_client_tuner = client;
	adap->fe[0] = frontend;

	return 0;
err_i2c_unregister_device:
	i2c_unregister_device(client);
err_module_put_demod:
	module_put(pdev->dev.driver->owner);
err_platform_device_unregister:
	platform_device_unregister(pdev);
err:
	dev_dbg(&intf->dev, "failed=%d\n", ret);
	return ret;
}