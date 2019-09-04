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
struct i2c_client {int dummy; } ;
struct fsa9480_usbsw {struct i2c_client* client; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int DEV_T1_CHARGER_MASK ; 
 int DEV_T1_UART_MASK ; 
 int DEV_T1_USB_MASK ; 
 int DEV_T2_JIG_MASK ; 
 int DEV_T2_UART_MASK ; 
 int DEV_T2_USB_MASK ; 
 int /*<<< orphan*/  FSA9480_REG_DEV_T1 ; 
 int /*<<< orphan*/  FSA9480_REG_DEV_T2 ; 
 struct fsa9480_usbsw* dev_get_drvdata (struct device*) ; 
 int fsa9480_read_reg (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t fsa9480_show_device(struct device *dev,
				   struct device_attribute *attr,
				   char *buf)
{
	struct fsa9480_usbsw *usbsw = dev_get_drvdata(dev);
	struct i2c_client *client = usbsw->client;
	int dev1, dev2;

	dev1 = fsa9480_read_reg(client, FSA9480_REG_DEV_T1);
	dev2 = fsa9480_read_reg(client, FSA9480_REG_DEV_T2);

	if (!dev1 && !dev2)
		return sprintf(buf, "NONE\n");

	/* USB */
	if (dev1 & DEV_T1_USB_MASK || dev2 & DEV_T2_USB_MASK)
		return sprintf(buf, "USB\n");

	/* UART */
	if (dev1 & DEV_T1_UART_MASK || dev2 & DEV_T2_UART_MASK)
		return sprintf(buf, "UART\n");

	/* CHARGER */
	if (dev1 & DEV_T1_CHARGER_MASK)
		return sprintf(buf, "CHARGER\n");

	/* JIG */
	if (dev2 & DEV_T2_JIG_MASK)
		return sprintf(buf, "JIG\n");

	return sprintf(buf, "UNKNOWN\n");
}