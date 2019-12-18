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
struct tps6507x_dev {int /*<<< orphan*/ * dev; int /*<<< orphan*/  write_dev; int /*<<< orphan*/  read_dev; struct i2c_client* i2c_client; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct tps6507x_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tps6507x_dev*) ; 
 int /*<<< orphan*/  tps6507x_devs ; 
 int /*<<< orphan*/  tps6507x_i2c_read_device ; 
 int /*<<< orphan*/  tps6507x_i2c_write_device ; 

__attribute__((used)) static int tps6507x_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct tps6507x_dev *tps6507x;

	tps6507x = devm_kzalloc(&i2c->dev, sizeof(struct tps6507x_dev),
				GFP_KERNEL);
	if (tps6507x == NULL)
		return -ENOMEM;

	i2c_set_clientdata(i2c, tps6507x);
	tps6507x->dev = &i2c->dev;
	tps6507x->i2c_client = i2c;
	tps6507x->read_dev = tps6507x_i2c_read_device;
	tps6507x->write_dev = tps6507x_i2c_write_device;

	return devm_mfd_add_devices(tps6507x->dev, -1, tps6507x_devs,
				    ARRAY_SIZE(tps6507x_devs), NULL, 0, NULL);
}