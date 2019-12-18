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
struct spi_mpc8xxx_cs {int dummy; } ;
struct spi_device {int mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int SPI_LSB_FIRST ; 

__attribute__((used)) static int mspi_apply_qe_mode_quirks(struct spi_mpc8xxx_cs *cs,
				struct spi_device *spi,
				int bits_per_word)
{
	/* QE uses Little Endian for words > 8
	 * so transform all words > 8 into 8 bits
	 * Unfortnatly that doesn't work for LSB so
	 * reject these for now */
	/* Note: 32 bits word, LSB works iff
	 * tfcr/rfcr is set to CPMFCR_GBL */
	if (spi->mode & SPI_LSB_FIRST &&
	    bits_per_word > 8)
		return -EINVAL;
	if (bits_per_word > 8)
		return 8; /* pretend its 8 bits */
	return bits_per_word;
}