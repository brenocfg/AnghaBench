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
struct uniphier_i2c_priv {unsigned int clk_cycle; scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ UNIPHIER_I2C_CLK ; 
 int /*<<< orphan*/  uniphier_i2c_reset (struct uniphier_i2c_priv*,int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void uniphier_i2c_hw_init(struct uniphier_i2c_priv *priv)
{
	unsigned int cyc = priv->clk_cycle;

	uniphier_i2c_reset(priv, true);

	/*
	 * Bit30-16: clock cycles of tLOW.
	 *  Standard-mode: tLOW = 4.7 us, tHIGH = 4.0 us
	 *  Fast-mode:     tLOW = 1.3 us, tHIGH = 0.6 us
	 * "tLow/tHIGH = 5/4" meets both.
	 */
	writel((cyc * 5 / 9 << 16) | cyc, priv->membase + UNIPHIER_I2C_CLK);

	uniphier_i2c_reset(priv, false);
}