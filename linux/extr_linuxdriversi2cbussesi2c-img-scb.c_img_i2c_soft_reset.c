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
struct img_i2c {int t_halt; } ;

/* Variables and functions */
 int SCB_CONTROL_CLK_ENABLE ; 
 int /*<<< orphan*/  SCB_CONTROL_REG ; 
 int SCB_CONTROL_SOFT_RESET ; 
 int /*<<< orphan*/  img_i2c_writel (struct img_i2c*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void img_i2c_soft_reset(struct img_i2c *i2c)
{
	i2c->t_halt = false;
	img_i2c_writel(i2c, SCB_CONTROL_REG, 0);
	img_i2c_writel(i2c, SCB_CONTROL_REG,
		       SCB_CONTROL_CLK_ENABLE | SCB_CONTROL_SOFT_RESET);
}