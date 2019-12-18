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
struct uniphier_fi2c_priv {int len; int enabled_irqs; scalar_t__ membase; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ UNIPHIER_FI2C_DTTX ; 
 int UNIPHIER_FI2C_DTTX_CMD ; 
 int UNIPHIER_FI2C_DTTX_RD ; 
 int UNIPHIER_FI2C_INT_RB ; 
 int UNIPHIER_FI2C_INT_RF ; 
 int /*<<< orphan*/  UNIPHIER_FI2C_MANUAL_NACK ; 
 scalar_t__ UNIPHIER_FI2C_RBC ; 
 int /*<<< orphan*/  UNIPHIER_FI2C_RD ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  uniphier_fi2c_set_irqs (struct uniphier_fi2c_priv*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void uniphier_fi2c_rx_init(struct uniphier_fi2c_priv *priv, u16 addr)
{
	priv->flags |= UNIPHIER_FI2C_RD;

	if (likely(priv->len < 256)) {
		/*
		 * If possible, use RX byte counter.
		 * It can automatically handle NACK for the last byte.
		 */
		writel(priv->len, priv->membase + UNIPHIER_FI2C_RBC);
		priv->enabled_irqs |= UNIPHIER_FI2C_INT_RF |
				      UNIPHIER_FI2C_INT_RB;
	} else {
		/*
		 * The byte counter can not count over 256.  In this case,
		 * do not use it at all.  Drain data when FIFO gets full,
		 * but treat the last portion as a special case.
		 */
		writel(0, priv->membase + UNIPHIER_FI2C_RBC);
		priv->flags |= UNIPHIER_FI2C_MANUAL_NACK;
		priv->enabled_irqs |= UNIPHIER_FI2C_INT_RF;
	}

	uniphier_fi2c_set_irqs(priv);

	/* set slave address with RD bit */
	writel(UNIPHIER_FI2C_DTTX_CMD | UNIPHIER_FI2C_DTTX_RD | addr << 1,
	       priv->membase + UNIPHIER_FI2C_DTTX);
}