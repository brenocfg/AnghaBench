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
typedef  int /*<<< orphan*/  u32 ;
struct i2c_adapter {int dummy; } ;
struct dw_i2c_dev {int /*<<< orphan*/  functionality; } ;

/* Variables and functions */
 struct dw_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 

u32 i2c_dw_func(struct i2c_adapter *adap)
{
	struct dw_i2c_dev *dev = i2c_get_adapdata(adap);

	return dev->functionality;
}