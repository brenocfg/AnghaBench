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
struct spi_device {int /*<<< orphan*/  chip_select; } ;
struct altera_spi {scalar_t__ base; int /*<<< orphan*/  imr; } ;

/* Variables and functions */
 scalar_t__ ALTERA_SPI_CONTROL ; 
 int /*<<< orphan*/  ALTERA_SPI_CONTROL_SSO_MSK ; 
 scalar_t__ ALTERA_SPI_SLAVE_SEL ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 struct altera_spi* altera_spi_to_hw (struct spi_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void altera_spi_set_cs(struct spi_device *spi, bool is_high)
{
	struct altera_spi *hw = altera_spi_to_hw(spi);

	if (is_high) {
		hw->imr &= ~ALTERA_SPI_CONTROL_SSO_MSK;
		writel(hw->imr, hw->base + ALTERA_SPI_CONTROL);
		writel(0, hw->base + ALTERA_SPI_SLAVE_SEL);
	} else {
		writel(BIT(spi->chip_select), hw->base + ALTERA_SPI_SLAVE_SEL);
		hw->imr |= ALTERA_SPI_CONTROL_SSO_MSK;
		writel(hw->imr, hw->base + ALTERA_SPI_CONTROL);
	}
}