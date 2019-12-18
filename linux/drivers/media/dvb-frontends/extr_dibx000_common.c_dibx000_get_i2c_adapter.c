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
struct i2c_adapter {int dummy; } ;
struct dibx000_i2c_master {struct i2c_adapter master_i2c_adap_gpio67; struct i2c_adapter master_i2c_adap_gpio34; struct i2c_adapter master_i2c_adap_gpio12; struct i2c_adapter gated_tuner_i2c_adap; } ;
typedef  enum dibx000_i2c_interface { ____Placeholder_dibx000_i2c_interface } dibx000_i2c_interface ;

/* Variables and functions */
#define  DIBX000_I2C_INTERFACE_GPIO_1_2 131 
#define  DIBX000_I2C_INTERFACE_GPIO_3_4 130 
#define  DIBX000_I2C_INTERFACE_GPIO_6_7 129 
#define  DIBX000_I2C_INTERFACE_TUNER 128 
 int /*<<< orphan*/  pr_err (char*) ; 

struct i2c_adapter *dibx000_get_i2c_adapter(struct dibx000_i2c_master *mst,
						enum dibx000_i2c_interface intf,
						int gating)
{
	struct i2c_adapter *i2c = NULL;

	switch (intf) {
	case DIBX000_I2C_INTERFACE_TUNER:
		if (gating)
			i2c = &mst->gated_tuner_i2c_adap;
		break;
	case DIBX000_I2C_INTERFACE_GPIO_1_2:
		if (!gating)
			i2c = &mst->master_i2c_adap_gpio12;
		break;
	case DIBX000_I2C_INTERFACE_GPIO_3_4:
		if (!gating)
			i2c = &mst->master_i2c_adap_gpio34;
		break;
	case DIBX000_I2C_INTERFACE_GPIO_6_7:
		if (gating)
			i2c = &mst->master_i2c_adap_gpio67;
		break;
	default:
		pr_err("incorrect I2C interface selected\n");
		break;
	}

	return i2c;
}