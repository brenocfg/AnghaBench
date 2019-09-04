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
struct sprd_i2c {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ ADDR_RST ; 
 int /*<<< orphan*/  I2C_RST ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sprd_i2c_reset_fifo(struct sprd_i2c *i2c_dev)
{
	writel(I2C_RST, i2c_dev->base + ADDR_RST);
}