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
struct synquacer_spi {scalar_t__ regs; } ;
struct spi_device {int chip_select; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int SYNQUACER_HSSPI_DMPSEL_CS_MASK ; 
 int SYNQUACER_HSSPI_DMPSEL_CS_SHIFT ; 
 scalar_t__ SYNQUACER_HSSPI_REG_DMSTART ; 
 int readl (scalar_t__) ; 
 struct synquacer_spi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void synquacer_spi_set_cs(struct spi_device *spi, bool enable)
{
	struct synquacer_spi *sspi = spi_master_get_devdata(spi->master);
	u32 val;

	val = readl(sspi->regs + SYNQUACER_HSSPI_REG_DMSTART);
	val &= ~(SYNQUACER_HSSPI_DMPSEL_CS_MASK <<
		 SYNQUACER_HSSPI_DMPSEL_CS_SHIFT);
	val |= spi->chip_select << SYNQUACER_HSSPI_DMPSEL_CS_SHIFT;
	writel(val, sspi->regs + SYNQUACER_HSSPI_REG_DMSTART);
}