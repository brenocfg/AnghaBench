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
typedef  int u8 ;
struct usb4604 {int /*<<< orphan*/  mode; struct device* dev; } ;
struct i2c_client {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  USB4604_MODE_HUB ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int i2c_master_send (struct i2c_client*,int*,int /*<<< orphan*/ ) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 int /*<<< orphan*/  usb4604_reset (struct usb4604*,int) ; 

__attribute__((used)) static int usb4604_connect(struct usb4604 *hub)
{
	struct device *dev = hub->dev;
	struct i2c_client *client = to_i2c_client(dev);
	int err;
	u8 connect_cmd[] = { 0xaa, 0x55, 0x00 };

	usb4604_reset(hub, 1);

	err = i2c_master_send(client, connect_cmd, ARRAY_SIZE(connect_cmd));
	if (err < 0) {
		usb4604_reset(hub, 0);
		return err;
	}

	hub->mode = USB4604_MODE_HUB;
	dev_dbg(dev, "switched to HUB mode\n");

	return 0;
}