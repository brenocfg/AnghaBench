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
typedef  int u32 ;
struct i2c_adapter {int dummy; } ;
struct axxia_i2c_dev {scalar_t__ base; } ;

/* Variables and functions */
 int BM_SCLC ; 
 int BM_SDAC ; 
 scalar_t__ I2C_BUS_MONITOR ; 
 struct axxia_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void axxia_i2c_set_scl(struct i2c_adapter *adap, int val)
{
	struct axxia_i2c_dev *idev = i2c_get_adapdata(adap);
	u32 tmp;

	/* Preserve SDA Control */
	tmp = readl(idev->base + I2C_BUS_MONITOR) & BM_SDAC;
	if (!val)
		tmp |= BM_SCLC;
	writel(tmp, idev->base + I2C_BUS_MONITOR);
}