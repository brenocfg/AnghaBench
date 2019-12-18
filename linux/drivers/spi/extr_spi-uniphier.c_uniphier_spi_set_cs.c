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
typedef  int /*<<< orphan*/  u32 ;
struct uniphier_spi_priv {scalar_t__ base; } ;
struct spi_device {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 scalar_t__ SSI_FPS ; 
 int /*<<< orphan*/  SSI_FPS_FSPOL ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct uniphier_spi_priv* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void uniphier_spi_set_cs(struct spi_device *spi, bool enable)
{
	struct uniphier_spi_priv *priv = spi_master_get_devdata(spi->master);
	u32 val;

	val = readl(priv->base + SSI_FPS);

	if (enable)
		val |= SSI_FPS_FSPOL;
	else
		val &= ~SSI_FPS_FSPOL;

	writel(val, priv->base + SSI_FPS);
}