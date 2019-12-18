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
struct pasemi_smbus {int dummy; } ;
struct i2c_msg {int dummy; } ;
struct i2c_adapter {struct pasemi_smbus* algo_data; } ;

/* Variables and functions */
 int pasemi_i2c_xfer_msg (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  pasemi_smb_clear (struct pasemi_smbus*) ; 

__attribute__((used)) static int pasemi_i2c_xfer(struct i2c_adapter *adapter,
			   struct i2c_msg *msgs, int num)
{
	struct pasemi_smbus *smbus = adapter->algo_data;
	int ret, i;

	pasemi_smb_clear(smbus);

	ret = 0;

	for (i = 0; i < num && !ret; i++)
		ret = pasemi_i2c_xfer_msg(adapter, &msgs[i], (i == (num - 1)));

	return ret ? ret : num;
}