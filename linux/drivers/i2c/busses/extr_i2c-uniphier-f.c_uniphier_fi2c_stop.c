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
struct uniphier_fi2c_priv {scalar_t__ membase; int /*<<< orphan*/  enabled_irqs; } ;

/* Variables and functions */
 scalar_t__ UNIPHIER_FI2C_CR ; 
 int UNIPHIER_FI2C_CR_MST ; 
 int UNIPHIER_FI2C_CR_STO ; 
 int /*<<< orphan*/  UNIPHIER_FI2C_INT_STOP ; 
 int /*<<< orphan*/  uniphier_fi2c_set_irqs (struct uniphier_fi2c_priv*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void uniphier_fi2c_stop(struct uniphier_fi2c_priv *priv)
{
	priv->enabled_irqs |= UNIPHIER_FI2C_INT_STOP;
	uniphier_fi2c_set_irqs(priv);
	writel(UNIPHIER_FI2C_CR_MST | UNIPHIER_FI2C_CR_STO,
	       priv->membase + UNIPHIER_FI2C_CR);
}