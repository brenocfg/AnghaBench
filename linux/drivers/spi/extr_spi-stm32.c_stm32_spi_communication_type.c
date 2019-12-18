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
struct spi_transfer {int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_device {int mode; } ;

/* Variables and functions */
 int SPI_3WIRE ; 
 unsigned int SPI_3WIRE_RX ; 
 unsigned int SPI_3WIRE_TX ; 
 unsigned int SPI_FULL_DUPLEX ; 
 unsigned int SPI_SIMPLEX_RX ; 
 unsigned int SPI_SIMPLEX_TX ; 

__attribute__((used)) static unsigned int stm32_spi_communication_type(struct spi_device *spi_dev,
						 struct spi_transfer *transfer)
{
	unsigned int type = SPI_FULL_DUPLEX;

	if (spi_dev->mode & SPI_3WIRE) { /* MISO/MOSI signals shared */
		/*
		 * SPI_3WIRE and xfer->tx_buf != NULL and xfer->rx_buf != NULL
		 * is forbidden and unvalidated by SPI subsystem so depending
		 * on the valid buffer, we can determine the direction of the
		 * transfer.
		 */
		if (!transfer->tx_buf)
			type = SPI_3WIRE_RX;
		else
			type = SPI_3WIRE_TX;
	} else {
		if (!transfer->tx_buf)
			type = SPI_SIMPLEX_RX;
		else if (!transfer->rx_buf)
			type = SPI_SIMPLEX_TX;
	}

	return type;
}