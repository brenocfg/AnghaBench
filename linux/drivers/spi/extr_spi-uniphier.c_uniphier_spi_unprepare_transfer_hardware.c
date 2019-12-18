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
struct uniphier_spi_priv {scalar_t__ base; } ;
struct spi_master {int dummy; } ;

/* Variables and functions */
 scalar_t__ SSI_CTL ; 
 struct uniphier_spi_priv* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int uniphier_spi_unprepare_transfer_hardware(struct spi_master *master)
{
	struct uniphier_spi_priv *priv = spi_master_get_devdata(master);

	writel(0, priv->base + SSI_CTL);

	return 0;
}