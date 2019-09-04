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
struct osif_priv {int /*<<< orphan*/  usb_dev; } ;
struct i2c_adapter {struct osif_priv* algo_data; } ;

/* Variables and functions */
 int USB_DIR_IN ; 
 int USB_RECIP_INTERFACE ; 
 int USB_TYPE_VENDOR ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,void*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int osif_usb_read(struct i2c_adapter *adapter, int cmd,
			 int value, int index, void *data, int len)
{
	struct osif_priv *priv = adapter->algo_data;

	return usb_control_msg(priv->usb_dev, usb_rcvctrlpipe(priv->usb_dev, 0),
			       cmd, USB_TYPE_VENDOR | USB_RECIP_INTERFACE |
			       USB_DIR_IN, value, index, data, len, 2000);
}