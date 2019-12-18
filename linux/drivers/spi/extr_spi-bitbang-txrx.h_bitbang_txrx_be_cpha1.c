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
typedef  int u8 ;
typedef  int u32 ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 unsigned int SPI_MASTER_NO_RX ; 
 unsigned int SPI_MASTER_NO_TX ; 
 int getmiso (struct spi_device*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  setmosi (struct spi_device*,int) ; 
 int /*<<< orphan*/  setsck (struct spi_device*,unsigned int) ; 
 int /*<<< orphan*/  spidelay (unsigned int) ; 

__attribute__((used)) static inline u32
bitbang_txrx_be_cpha1(struct spi_device *spi,
		unsigned nsecs, unsigned cpol, unsigned flags,
		u32 word, u8 bits)
{
	/* if (cpol == 0) this is SPI_MODE_1; else this is SPI_MODE_3 */

	u32 oldbit = (!(word & (1<<(bits-1)))) << 31;
	/* clock starts at inactive polarity */
	for (word <<= (32 - bits); likely(bits); bits--) {

		/* setup MSB (to slave) on leading edge */
		setsck(spi, !cpol);
		if ((flags & SPI_MASTER_NO_TX) == 0) {
			if ((word & (1 << 31)) != oldbit) {
				setmosi(spi, word & (1 << 31));
				oldbit = word & (1 << 31);
			}
		}
		spidelay(nsecs); /* T(setup) */

		setsck(spi, cpol);
		spidelay(nsecs);

		/* sample MSB (from slave) on trailing edge */
		word <<= 1;
		if ((flags & SPI_MASTER_NO_RX) == 0)
			word |= getmiso(spi);
	}
	return word;
}