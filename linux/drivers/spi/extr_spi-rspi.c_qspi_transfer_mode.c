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
typedef  int u16 ;
struct spi_transfer {int tx_nbits; int rx_nbits; scalar_t__ rx_buf; scalar_t__ tx_buf; } ;

/* Variables and functions */
 int SPCMD_SPIMOD_DUAL ; 
 int SPCMD_SPIMOD_QUAD ; 
 int SPCMD_SPRW ; 
#define  SPI_NBITS_DUAL 129 
#define  SPI_NBITS_QUAD 128 

__attribute__((used)) static u16 qspi_transfer_mode(const struct spi_transfer *xfer)
{
	if (xfer->tx_buf)
		switch (xfer->tx_nbits) {
		case SPI_NBITS_QUAD:
			return SPCMD_SPIMOD_QUAD;
		case SPI_NBITS_DUAL:
			return SPCMD_SPIMOD_DUAL;
		default:
			return 0;
		}
	if (xfer->rx_buf)
		switch (xfer->rx_nbits) {
		case SPI_NBITS_QUAD:
			return SPCMD_SPIMOD_QUAD | SPCMD_SPRW;
		case SPI_NBITS_DUAL:
			return SPCMD_SPIMOD_DUAL | SPCMD_SPRW;
		default:
			return 0;
		}

	return 0;
}