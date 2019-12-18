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
typedef  int u32 ;
struct uniphier_spi_priv {scalar_t__ base; int /*<<< orphan*/  clk; } ;
struct spi_device {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ SSI_CKS ; 
 int SSI_CKS_CKRAT_MASK ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int round_up (int,int) ; 
 struct uniphier_spi_priv* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void uniphier_spi_set_baudrate(struct spi_device *spi,
				      unsigned int speed)
{
	struct uniphier_spi_priv *priv = spi_master_get_devdata(spi->master);
	u32 val, ckdiv;

	/*
	 * the supported rates are even numbers from 4 to 254. (4,6,8...254)
	 * round up as we look for equal or less speed
	 */
	ckdiv = DIV_ROUND_UP(clk_get_rate(priv->clk), speed);
	ckdiv = round_up(ckdiv, 2);

	val = readl(priv->base + SSI_CKS);
	val &= ~SSI_CKS_CKRAT_MASK;
	val |= ckdiv & SSI_CKS_CKRAT_MASK;
	writel(val, priv->base + SSI_CKS);
}