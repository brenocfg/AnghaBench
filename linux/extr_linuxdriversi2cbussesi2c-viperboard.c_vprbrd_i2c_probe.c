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
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_6__* parent; } ;
struct TYPE_11__ {TYPE_2__ dev; int /*<<< orphan*/  name; struct vprbrd* algo_data; int /*<<< orphan*/ * quirks; int /*<<< orphan*/ * algo; int /*<<< orphan*/  class; int /*<<< orphan*/  owner; } ;
struct vprbrd_i2c {TYPE_5__ i2c; scalar_t__ bus_freq_param; } ;
struct vprbrd {TYPE_3__* usb_dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_6__ dev; } ;
struct TYPE_10__ {int devnum; TYPE_1__* bus; } ;
struct TYPE_8__ {int busnum; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLASS_HWMON ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ VPRBRD_I2C_FREQ_10KHZ ; 
 scalar_t__ VPRBRD_I2C_FREQ_6MHZ ; 
 int /*<<< orphan*/  VPRBRD_USB_REQUEST_I2C_FREQ ; 
 int /*<<< orphan*/  VPRBRD_USB_TIMEOUT_MS ; 
 int /*<<< orphan*/  VPRBRD_USB_TYPE_OUT ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*,int /*<<< orphan*/ ) ; 
 struct vprbrd* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct vprbrd_i2c* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_add_adapter (TYPE_5__*) ; 
 int /*<<< orphan*/  i2c_bus_freq ; 
 scalar_t__ i2c_bus_param ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct vprbrd_i2c*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int usb_control_msg (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int usb_sndctrlpipe (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vprbrd_algorithm ; 
 int /*<<< orphan*/  vprbrd_quirks ; 

__attribute__((used)) static int vprbrd_i2c_probe(struct platform_device *pdev)
{
	struct vprbrd *vb = dev_get_drvdata(pdev->dev.parent);
	struct vprbrd_i2c *vb_i2c;
	int ret;
	int pipe;

	vb_i2c = devm_kzalloc(&pdev->dev, sizeof(*vb_i2c), GFP_KERNEL);
	if (vb_i2c == NULL)
		return -ENOMEM;

	/* setup i2c adapter description */
	vb_i2c->i2c.owner = THIS_MODULE;
	vb_i2c->i2c.class = I2C_CLASS_HWMON;
	vb_i2c->i2c.algo = &vprbrd_algorithm;
	vb_i2c->i2c.quirks = &vprbrd_quirks;
	vb_i2c->i2c.algo_data = vb;
	/* save the param in usb capabable memory */
	vb_i2c->bus_freq_param = i2c_bus_param;

	snprintf(vb_i2c->i2c.name, sizeof(vb_i2c->i2c.name),
		 "viperboard at bus %03d device %03d",
		 vb->usb_dev->bus->busnum, vb->usb_dev->devnum);

	/* setting the bus frequency */
	if ((i2c_bus_param <= VPRBRD_I2C_FREQ_10KHZ)
		&& (i2c_bus_param >= VPRBRD_I2C_FREQ_6MHZ)) {
		pipe = usb_sndctrlpipe(vb->usb_dev, 0);
		ret = usb_control_msg(vb->usb_dev, pipe,
			VPRBRD_USB_REQUEST_I2C_FREQ, VPRBRD_USB_TYPE_OUT,
			0x0000, 0x0000, &vb_i2c->bus_freq_param, 1,
			VPRBRD_USB_TIMEOUT_MS);
		if (ret != 1) {
			dev_err(&pdev->dev, "failure setting i2c_bus_freq to %d\n",
				i2c_bus_freq);
			return -EIO;
		}
	} else {
		dev_err(&pdev->dev,
			"invalid i2c_bus_freq setting:%d\n", i2c_bus_freq);
		return -EIO;
	}

	vb_i2c->i2c.dev.parent = &pdev->dev;

	/* attach to i2c layer */
	i2c_add_adapter(&vb_i2c->i2c);

	platform_set_drvdata(pdev, vb_i2c);

	return 0;
}