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
typedef  int u16 ;
struct uniphier_fi2c_priv {scalar_t__ membase; int /*<<< orphan*/  enabled_irqs; } ;

/* Variables and functions */
 scalar_t__ UNIPHIER_FI2C_DTTX ; 
 int UNIPHIER_FI2C_DTTX_CMD ; 
 int /*<<< orphan*/  UNIPHIER_FI2C_INT_TE ; 
 scalar_t__ UNIPHIER_FI2C_TBC ; 
 int /*<<< orphan*/  uniphier_fi2c_fill_txfifo (struct uniphier_fi2c_priv*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void uniphier_fi2c_tx_init(struct uniphier_fi2c_priv *priv, u16 addr)
{
	priv->enabled_irqs |= UNIPHIER_FI2C_INT_TE;
	/* do not use TX byte counter */
	writel(0, priv->membase + UNIPHIER_FI2C_TBC);
	/* set slave address */
	writel(UNIPHIER_FI2C_DTTX_CMD | addr << 1,
	       priv->membase + UNIPHIER_FI2C_DTTX);
	/* first chunk of data */
	uniphier_fi2c_fill_txfifo(priv, true);
}