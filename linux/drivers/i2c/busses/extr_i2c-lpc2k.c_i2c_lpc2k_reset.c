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
struct lpc2k_i2c {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC24XX_CLEAR_ALL ; 
 scalar_t__ LPC24XX_I2ADDR ; 
 scalar_t__ LPC24XX_I2CONCLR ; 
 scalar_t__ LPC24XX_I2CONSET ; 
 int /*<<< orphan*/  LPC24XX_I2EN ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void i2c_lpc2k_reset(struct lpc2k_i2c *i2c)
{
	/* Will force clear all statuses */
	writel(LPC24XX_CLEAR_ALL, i2c->base + LPC24XX_I2CONCLR);
	writel(0, i2c->base + LPC24XX_I2ADDR);
	writel(LPC24XX_I2EN, i2c->base + LPC24XX_I2CONSET);
}