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
struct sifive_spi {int /*<<< orphan*/  done; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int SIFIVE_SPI_IP_RXWM ; 
 int SIFIVE_SPI_IP_TXWM ; 
 int /*<<< orphan*/  SIFIVE_SPI_REG_IE ; 
 int /*<<< orphan*/  SIFIVE_SPI_REG_IP ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int sifive_spi_read (struct sifive_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sifive_spi_write (struct sifive_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t sifive_spi_irq(int irq, void *dev_id)
{
	struct sifive_spi *spi = dev_id;
	u32 ip = sifive_spi_read(spi, SIFIVE_SPI_REG_IP);

	if (ip & (SIFIVE_SPI_IP_TXWM | SIFIVE_SPI_IP_RXWM)) {
		/* Disable interrupts until next transfer */
		sifive_spi_write(spi, SIFIVE_SPI_REG_IE, 0);
		complete(&spi->done);
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}