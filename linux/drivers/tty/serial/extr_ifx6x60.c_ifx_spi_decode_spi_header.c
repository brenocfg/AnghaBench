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

/* Variables and functions */
 unsigned char IFX_SPI_CTS_BIT ; 
 int IFX_SPI_HEADER_0 ; 
 int IFX_SPI_HEADER_F ; 
 unsigned char IFX_SPI_MORE_BIT ; 

__attribute__((used)) static int ifx_spi_decode_spi_header(unsigned char *buffer, int *length,
			unsigned char *more, unsigned char *received_cts)
{
	u16 h1;
	u16 h2;
	u16 *in_buffer = (u16 *)buffer;

	h1 = *in_buffer;
	h2 = *(in_buffer+1);

	if (h1 == 0 && h2 == 0) {
		*received_cts = 0;
		*more = 0;
		return IFX_SPI_HEADER_0;
	} else if (h1 == 0xffff && h2 == 0xffff) {
		*more = 0;
		/* spi_slave_cts remains as it was */
		return IFX_SPI_HEADER_F;
	}

	*length = h1 & 0xfff;	/* upper bits of byte are flags */
	*more = (buffer[1] >> IFX_SPI_MORE_BIT) & 1;
	*received_cts = (buffer[3] >> IFX_SPI_CTS_BIT) & 1;
	return 0;
}