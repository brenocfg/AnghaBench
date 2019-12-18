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
typedef  int /*<<< orphan*/  uint8_t ;
struct i2c_algo_dp_aux_data {int (* aux_ch ) (struct i2c_adapter*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct i2c_adapter {struct i2c_algo_dp_aux_data* algo_data; } ;

/* Variables and functions */
 int stub1 (struct i2c_adapter*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
i2c_algo_dp_aux_transaction(struct i2c_adapter *adapter, int mode,
			    uint8_t write_byte, uint8_t *read_byte)
{
	struct i2c_algo_dp_aux_data *algo_data = adapter->algo_data;
	int ret;

	ret = (*algo_data->aux_ch)(adapter, mode,
				   write_byte, read_byte);
	return ret;
}