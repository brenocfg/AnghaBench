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
struct altera_spi {unsigned int* rx; int bytes_per_word; size_t count; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ ALTERA_SPI_RXDATA ; 
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static void altera_spi_rx_word(struct altera_spi *hw)
{
	unsigned int rxd;

	rxd = readl(hw->base + ALTERA_SPI_RXDATA);
	if (hw->rx) {
		switch (hw->bytes_per_word) {
		case 1:
			hw->rx[hw->count] = rxd;
			break;
		case 2:
			hw->rx[hw->count * 2] = rxd;
			hw->rx[hw->count * 2 + 1] = rxd >> 8;
			break;
		}
	}

	hw->count++;
}