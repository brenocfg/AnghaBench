#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; TYPE_4__* adapter; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_9__ {struct tm6000_core* algo_data; int /*<<< orphan*/  name; TYPE_1__ dev; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; } ;
struct tm6000_core {char* name; TYPE_3__ i2c_client; TYPE_4__ i2c_adap; int /*<<< orphan*/  v4l2_dev; TYPE_2__* udev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int I2C_NAME_SIZE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int i2c_add_adapter (TYPE_4__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tm6000_algo ; 
 int /*<<< orphan*/  tm6000_i2c_eeprom (struct tm6000_core*) ; 

int tm6000_i2c_register(struct tm6000_core *dev)
{
	int rc;

	dev->i2c_adap.owner = THIS_MODULE;
	dev->i2c_adap.algo = &tm6000_algo;
	dev->i2c_adap.dev.parent = &dev->udev->dev;
	strscpy(dev->i2c_adap.name, dev->name, sizeof(dev->i2c_adap.name));
	dev->i2c_adap.algo_data = dev;
	i2c_set_adapdata(&dev->i2c_adap, &dev->v4l2_dev);
	rc = i2c_add_adapter(&dev->i2c_adap);
	if (rc)
		return rc;

	dev->i2c_client.adapter = &dev->i2c_adap;
	strscpy(dev->i2c_client.name, "tm6000 internal", I2C_NAME_SIZE);
	tm6000_i2c_eeprom(dev);

	return 0;
}