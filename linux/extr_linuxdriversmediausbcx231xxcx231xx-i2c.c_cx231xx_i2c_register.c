#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {struct cx231xx_i2c* algo_data; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct cx231xx_i2c {int nr; scalar_t__ i2c_rc; TYPE_2__ i2c_adap; struct cx231xx* dev; } ;
struct cx231xx {char* name; int /*<<< orphan*/  dev; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  cx231xx_send_usb_command; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_2__ cx231xx_adap_template ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ i2c_add_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 

int cx231xx_i2c_register(struct cx231xx_i2c *bus)
{
	struct cx231xx *dev = bus->dev;

	BUG_ON(!dev->cx231xx_send_usb_command);

	bus->i2c_adap = cx231xx_adap_template;
	bus->i2c_adap.dev.parent = dev->dev;

	snprintf(bus->i2c_adap.name, sizeof(bus->i2c_adap.name), "%s-%d", bus->dev->name, bus->nr);

	bus->i2c_adap.algo_data = bus;
	i2c_set_adapdata(&bus->i2c_adap, &dev->v4l2_dev);
	bus->i2c_rc = i2c_add_adapter(&bus->i2c_adap);

	if (0 != bus->i2c_rc)
		dev_warn(dev->dev,
			 "i2c bus %d register FAILED\n", bus->nr);

	return bus->i2c_rc;
}