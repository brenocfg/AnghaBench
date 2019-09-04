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
typedef  unsigned int u32 ;
struct uniphier_fi2c_priv {unsigned int clk_cycle; scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ UNIPHIER_FI2C_CR ; 
 unsigned int UNIPHIER_FI2C_CR_MST ; 
 scalar_t__ UNIPHIER_FI2C_CYC ; 
 scalar_t__ UNIPHIER_FI2C_DSUT ; 
 scalar_t__ UNIPHIER_FI2C_LCTL ; 
 scalar_t__ UNIPHIER_FI2C_SSUT ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  uniphier_fi2c_prepare_operation (struct uniphier_fi2c_priv*) ; 
 int /*<<< orphan*/  uniphier_fi2c_reset (struct uniphier_fi2c_priv*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void uniphier_fi2c_hw_init(struct uniphier_fi2c_priv *priv)
{
	unsigned int cyc = priv->clk_cycle;
	u32 tmp;

	tmp = readl(priv->membase + UNIPHIER_FI2C_CR);
	tmp |= UNIPHIER_FI2C_CR_MST;
	writel(tmp, priv->membase + UNIPHIER_FI2C_CR);

	uniphier_fi2c_reset(priv);

	/*
	 *  Standard-mode: tLOW + tHIGH = 10 us
	 *  Fast-mode:     tLOW + tHIGH = 2.5 us
	 */
	writel(cyc, priv->membase + UNIPHIER_FI2C_CYC);
	/*
	 *  Standard-mode: tLOW = 4.7 us, tHIGH = 4.0 us, tBUF = 4.7 us
	 *  Fast-mode:     tLOW = 1.3 us, tHIGH = 0.6 us, tBUF = 1.3 us
	 * "tLow/tHIGH = 5/4" meets both.
	 */
	writel(cyc * 5 / 9, priv->membase + UNIPHIER_FI2C_LCTL);
	/*
	 *  Standard-mode: tHD;STA = 4.0 us, tSU;STA = 4.7 us, tSU;STO = 4.0 us
	 *  Fast-mode:     tHD;STA = 0.6 us, tSU;STA = 0.6 us, tSU;STO = 0.6 us
	 */
	writel(cyc / 2, priv->membase + UNIPHIER_FI2C_SSUT);
	/*
	 *  Standard-mode: tSU;DAT = 250 ns
	 *  Fast-mode:     tSU;DAT = 100 ns
	 */
	writel(cyc / 16, priv->membase + UNIPHIER_FI2C_DSUT);

	uniphier_fi2c_prepare_operation(priv);
}