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
struct TYPE_2__ {struct device* parent; } ;
struct i2c_adapter {int class; TYPE_1__ dev; int /*<<< orphan*/ * algo; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct scx200_acb_iface {int /*<<< orphan*/  mutex; struct i2c_adapter adapter; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_CLASS_HWMON ; 
 int I2C_CLASS_SPD ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  i2c_set_adapdata (struct i2c_adapter*,struct scx200_acb_iface*) ; 
 struct scx200_acb_iface* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scx200_acb_algorithm ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*,int) ; 

__attribute__((used)) static struct scx200_acb_iface *scx200_create_iface(const char *text,
		struct device *dev, int index)
{
	struct scx200_acb_iface *iface;
	struct i2c_adapter *adapter;

	iface = kzalloc(sizeof(*iface), GFP_KERNEL);
	if (!iface)
		return NULL;

	adapter = &iface->adapter;
	i2c_set_adapdata(adapter, iface);
	snprintf(adapter->name, sizeof(adapter->name), "%s ACB%d", text, index);
	adapter->owner = THIS_MODULE;
	adapter->algo = &scx200_acb_algorithm;
	adapter->class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	adapter->dev.parent = dev;

	mutex_init(&iface->mutex);

	return iface;
}