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
struct zx2967_i2c {int dummy; } ;
struct i2c_msg {int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 struct zx2967_i2c* i2c_get_adapdata (struct i2c_adapter*) ; 
 int zx2967_i2c_xfer_msg (struct zx2967_i2c*,struct i2c_msg*) ; 
 int /*<<< orphan*/  zx2967_set_addr (struct zx2967_i2c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zx2967_i2c_xfer(struct i2c_adapter *adap,
			   struct i2c_msg *msgs, int num)
{
	struct zx2967_i2c *i2c = i2c_get_adapdata(adap);
	int ret;
	int i;

	zx2967_set_addr(i2c, msgs->addr);

	for (i = 0; i < num; i++) {
		ret = zx2967_i2c_xfer_msg(i2c, &msgs[i]);
		if (ret)
			return ret;
	}

	return num;
}