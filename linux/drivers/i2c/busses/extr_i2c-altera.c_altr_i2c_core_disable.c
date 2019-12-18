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
struct altr_i2c_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ ALTR_I2C_CTRL ; 
 int ALTR_I2C_CTRL_EN ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void altr_i2c_core_disable(struct altr_i2c_dev *idev)
{
	u32 tmp = readl(idev->base + ALTR_I2C_CTRL);

	writel(tmp & ~ALTR_I2C_CTRL_EN, idev->base + ALTR_I2C_CTRL);
}