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
struct i2c_adapter {int dummy; } ;
struct altr_i2c_dev {int dummy; } ;

/* Variables and functions */
 int altr_i2c_xfer_msg (struct altr_i2c_dev*,int /*<<< orphan*/ ) ; 
 struct altr_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 

__attribute__((used)) static int
altr_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs, int num)
{
	struct altr_i2c_dev *idev = i2c_get_adapdata(adap);
	int i, ret;

	for (i = 0; i < num; i++) {
		ret = altr_i2c_xfer_msg(idev, msgs++);
		if (ret)
			return ret;
	}
	return num;
}