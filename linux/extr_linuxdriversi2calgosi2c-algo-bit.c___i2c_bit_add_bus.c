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
struct i2c_algo_bit_data {int /*<<< orphan*/ * getscl; } ;
struct i2c_adapter {int retries; int /*<<< orphan*/  dev; int /*<<< orphan*/ * quirks; int /*<<< orphan*/ * algo; struct i2c_algo_bit_data* algo_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int bit_test ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_bit_algo ; 
 int /*<<< orphan*/  i2c_bit_quirk_no_clk_stretch ; 
 int test_bus (struct i2c_adapter*) ; 

__attribute__((used)) static int __i2c_bit_add_bus(struct i2c_adapter *adap,
			     int (*add_adapter)(struct i2c_adapter *))
{
	struct i2c_algo_bit_data *bit_adap = adap->algo_data;
	int ret;

	if (bit_test) {
		ret = test_bus(adap);
		if (bit_test >= 2 && ret < 0)
			return -ENODEV;
	}

	/* register new adapter to i2c module... */
	adap->algo = &i2c_bit_algo;
	adap->retries = 3;
	if (bit_adap->getscl == NULL)
		adap->quirks = &i2c_bit_quirk_no_clk_stretch;

	/*
	 * We tried forcing SCL/SDA to an initial state here. But that caused a
	 * regression, sadly. Check Bugzilla #200045 for details.
	 */

	ret = add_adapter(adap);
	if (ret < 0)
		return ret;

	/* Complain if SCL can't be read */
	if (bit_adap->getscl == NULL) {
		dev_warn(&adap->dev, "Not I2C compliant: can't read SCL\n");
		dev_warn(&adap->dev, "Bus may be unreliable\n");
	}
	return 0;
}