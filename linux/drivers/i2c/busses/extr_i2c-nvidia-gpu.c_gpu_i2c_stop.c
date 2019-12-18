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
struct gpu_i2c_dev {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ I2C_MST_CNTL ; 
 int /*<<< orphan*/  I2C_MST_CNTL_GEN_STOP ; 
 int gpu_i2c_check_status (struct gpu_i2c_dev*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int gpu_i2c_stop(struct gpu_i2c_dev *i2cd)
{
	writel(I2C_MST_CNTL_GEN_STOP, i2cd->regs + I2C_MST_CNTL);
	return gpu_i2c_check_status(i2cd);
}