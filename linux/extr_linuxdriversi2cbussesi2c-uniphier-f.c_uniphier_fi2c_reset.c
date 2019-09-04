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
struct uniphier_fi2c_priv {scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ UNIPHIER_FI2C_RST ; 
 int /*<<< orphan*/  UNIPHIER_FI2C_RST_RST ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void uniphier_fi2c_reset(struct uniphier_fi2c_priv *priv)
{
	writel(UNIPHIER_FI2C_RST_RST, priv->membase + UNIPHIER_FI2C_RST);
}