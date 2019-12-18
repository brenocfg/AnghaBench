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
struct dw_i2c_dev {int /*<<< orphan*/  rst; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_dw_disable (struct dw_i2c_dev*) ; 
 int /*<<< orphan*/  i2c_dw_prepare_clk (struct dw_i2c_dev*,int) ; 
 struct dw_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i2c_dw_prepare_recovery(struct i2c_adapter *adap)
{
	struct dw_i2c_dev *dev = i2c_get_adapdata(adap);

	i2c_dw_disable(dev);
	reset_control_assert(dev->rst);
	i2c_dw_prepare_clk(dev, false);
}