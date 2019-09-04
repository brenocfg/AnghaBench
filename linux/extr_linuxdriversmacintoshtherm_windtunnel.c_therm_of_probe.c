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
struct platform_device {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_2__ {scalar_t__ running; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  do_attach (struct i2c_adapter*) ; 
 int /*<<< orphan*/  g4fan_driver ; 
 int i2c_add_driver (int /*<<< orphan*/ *) ; 
 struct i2c_adapter* i2c_get_adapter (int) ; 
 int /*<<< orphan*/  i2c_put_adapter (struct i2c_adapter*) ; 
 TYPE_1__ x ; 

__attribute__((used)) static int therm_of_probe(struct platform_device *dev)
{
	struct i2c_adapter *adap;
	int ret, i = 0;

	adap = i2c_get_adapter(0);
	if (!adap)
		return -EPROBE_DEFER;

	ret = i2c_add_driver(&g4fan_driver);
	if (ret) {
		i2c_put_adapter(adap);
		return ret;
	}

	/* We assume Macs have consecutive I2C bus numbers starting at 0 */
	while (adap) {
		do_attach(adap);
		if (x.running)
			return 0;
		i2c_put_adapter(adap);
		adap = i2c_get_adapter(++i);
	}

	return -ENODEV;
}