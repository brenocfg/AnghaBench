#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct stm32_spi {TYPE_3__* cfg; scalar_t__ base; } ;
struct TYPE_6__ {TYPE_2__* regs; } ;
struct TYPE_4__ {int mask; int shift; scalar_t__ reg; } ;
struct TYPE_5__ {TYPE_1__ br; } ;

/* Variables and functions */
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void stm32_spi_set_mbr(struct stm32_spi *spi, u32 mbrdiv)
{
	u32 clrb = 0, setb = 0;

	clrb |= spi->cfg->regs->br.mask;
	setb |= ((u32)mbrdiv << spi->cfg->regs->br.shift) &
		spi->cfg->regs->br.mask;

	writel_relaxed((readl_relaxed(spi->base + spi->cfg->regs->br.reg) &
			~clrb) | setb,
		       spi->base + spi->cfg->regs->br.reg);
}