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
struct img_i2c {scalar_t__ need_wr_rd_fence; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCB_CORE_REV_REG ; 
 int /*<<< orphan*/  img_i2c_writel (struct img_i2c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void img_i2c_wr_rd_fence(struct img_i2c *i2c)
{
	if (i2c->need_wr_rd_fence) {
		img_i2c_writel(i2c, SCB_CORE_REV_REG, 0);
		img_i2c_writel(i2c, SCB_CORE_REV_REG, 0);
	}
}