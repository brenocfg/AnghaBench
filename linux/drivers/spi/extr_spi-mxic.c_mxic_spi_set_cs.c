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
struct spi_device {int /*<<< orphan*/  master; } ;
struct mxic_spi {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ HC_CFG ; 
 int HC_CFG_MAN_CS_ASSERT ; 
 int HC_CFG_MAN_CS_EN ; 
 scalar_t__ HC_EN ; 
 int HC_EN_BIT ; 
 int readl (scalar_t__) ; 
 struct mxic_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mxic_spi_set_cs(struct spi_device *spi, bool lvl)
{
	struct mxic_spi *mxic = spi_master_get_devdata(spi->master);

	if (!lvl) {
		writel(readl(mxic->regs + HC_CFG) | HC_CFG_MAN_CS_EN,
		       mxic->regs + HC_CFG);
		writel(HC_EN_BIT, mxic->regs + HC_EN);
		writel(readl(mxic->regs + HC_CFG) | HC_CFG_MAN_CS_ASSERT,
		       mxic->regs + HC_CFG);
	} else {
		writel(readl(mxic->regs + HC_CFG) & ~HC_CFG_MAN_CS_ASSERT,
		       mxic->regs + HC_CFG);
		writel(0, mxic->regs + HC_EN);
	}
}