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
struct tiny_spi {unsigned int baud; scalar_t__ speed_hz; unsigned int mode; scalar_t__ base; } ;
struct spi_transfer {scalar_t__ speed_hz; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TINY_SPI_BAUD ; 
 scalar_t__ TINY_SPI_CONTROL ; 
 unsigned int tiny_spi_baud (struct spi_device*,scalar_t__) ; 
 struct tiny_spi* tiny_spi_to_hw (struct spi_device*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int tiny_spi_setup_transfer(struct spi_device *spi,
				   struct spi_transfer *t)
{
	struct tiny_spi *hw = tiny_spi_to_hw(spi);
	unsigned int baud = hw->baud;

	if (t) {
		if (t->speed_hz && t->speed_hz != hw->speed_hz)
			baud = tiny_spi_baud(spi, t->speed_hz);
	}
	writel(baud, hw->base + TINY_SPI_BAUD);
	writel(hw->mode, hw->base + TINY_SPI_CONTROL);
	return 0;
}