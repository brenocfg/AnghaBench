#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; struct osif_priv* algo_data; int /*<<< orphan*/ * algo; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct osif_priv {TYPE_3__* usb_dev; TYPE_5__ adapter; struct usb_interface* interface; } ;
struct TYPE_7__ {int /*<<< orphan*/  bcdDevice; } ;
struct TYPE_9__ {int devnum; TYPE_2__* bus; TYPE_1__ descriptor; } ;
struct TYPE_8__ {int busnum; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_HWMON ; 
 int /*<<< orphan*/  OSIFI2C_SET_BIT_RATE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int,int,int) ; 
 struct osif_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_add_adapter (TYPE_5__*) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osif_algorithm ; 
 int osif_usb_read (TYPE_5__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 TYPE_3__* usb_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_dev (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct osif_priv*) ; 

__attribute__((used)) static int osif_probe(struct usb_interface *interface,
			     const struct usb_device_id *id)
{
	int ret;
	struct osif_priv *priv;
	u16 version;

	priv = devm_kzalloc(&interface->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->usb_dev = usb_get_dev(interface_to_usbdev(interface));
	priv->interface = interface;

	usb_set_intfdata(interface, priv);

	priv->adapter.owner = THIS_MODULE;
	priv->adapter.class = I2C_CLASS_HWMON;
	priv->adapter.algo = &osif_algorithm;
	priv->adapter.algo_data = priv;
	snprintf(priv->adapter.name, sizeof(priv->adapter.name),
		 "OSIF at bus %03d device %03d",
		 priv->usb_dev->bus->busnum, priv->usb_dev->devnum);

	/*
	 * Set bus frequency. The frequency is:
	 * 120,000,000 / ( 16 + 2 * div * 4^prescale).
	 * Using dev = 52, prescale = 0 give 100KHz */
	ret = osif_usb_read(&priv->adapter, OSIFI2C_SET_BIT_RATE, 52, 0,
			    NULL, 0);
	if (ret) {
		dev_err(&interface->dev, "failure sending bit rate");
		usb_put_dev(priv->usb_dev);
		return ret;
	}

	i2c_add_adapter(&(priv->adapter));

	version = le16_to_cpu(priv->usb_dev->descriptor.bcdDevice);
	dev_info(&interface->dev,
		 "version %x.%02x found at bus %03d address %03d",
		 version >> 8, version & 0xff,
		 priv->usb_dev->bus->busnum, priv->usb_dev->devnum);

	return 0;
}