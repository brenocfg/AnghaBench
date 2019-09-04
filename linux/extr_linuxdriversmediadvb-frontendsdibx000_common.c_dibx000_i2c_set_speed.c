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
typedef  int u16 ;
struct i2c_adapter {int dummy; } ;
struct dibx000_i2c_master {scalar_t__ device_rev; scalar_t__ base_reg; } ;

/* Variables and functions */
 scalar_t__ DIB7000MC ; 
 int dibx000_write_word (struct dibx000_i2c_master*,scalar_t__,int) ; 
 struct dibx000_i2c_master* i2c_get_adapdata (struct i2c_adapter*) ; 

int dibx000_i2c_set_speed(struct i2c_adapter *i2c_adap, u16 speed)
{
	struct dibx000_i2c_master *mst = i2c_get_adapdata(i2c_adap);

	if (mst->device_rev < DIB7000MC && speed < 235)
		speed = 235;
	return dibx000_write_word(mst, mst->base_reg + 3, (u16)(60000 / speed));

}