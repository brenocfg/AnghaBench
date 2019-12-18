#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct cm3323_data {int reg_conf; int /*<<< orphan*/  client; } ;
struct TYPE_3__ {int val; int val2; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CM3323_CMD_CONF ; 
 int CM3323_CONF_IT_MASK ; 
 int CM3323_CONF_IT_SHIFT ; 
 int EINVAL ; 
 TYPE_1__* cm3323_int_time ; 
 int i2c_smbus_write_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cm3323_set_it_bits(struct cm3323_data *data, int val, int val2)
{
	int i, ret;
	u16 reg_conf;

	for (i = 0; i < ARRAY_SIZE(cm3323_int_time); i++) {
		if (val == cm3323_int_time[i].val &&
		    val2 == cm3323_int_time[i].val2) {
			reg_conf = data->reg_conf & ~CM3323_CONF_IT_MASK;
			reg_conf |= i << CM3323_CONF_IT_SHIFT;

			ret = i2c_smbus_write_word_data(data->client,
							CM3323_CMD_CONF,
							reg_conf);
			if (ret < 0)
				return ret;

			data->reg_conf = reg_conf;

			return 0;
		}
	}

	return -EINVAL;
}