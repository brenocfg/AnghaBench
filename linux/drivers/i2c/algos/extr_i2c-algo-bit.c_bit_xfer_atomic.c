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
struct i2c_msg {int dummy; } ;
struct i2c_algo_bit_data {int /*<<< orphan*/  can_do_atomic; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; struct i2c_algo_bit_data* algo_data; } ;

/* Variables and functions */
 int bit_xfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int bit_xfer_atomic(struct i2c_adapter *i2c_adap, struct i2c_msg msgs[],
			   int num)
{
	struct i2c_algo_bit_data *adap = i2c_adap->algo_data;

	if (!adap->can_do_atomic)
		dev_warn(&i2c_adap->dev, "not flagged for atomic transfers\n");

	return bit_xfer(i2c_adap, msgs, num);
}