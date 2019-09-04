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
typedef  unsigned int u32 ;
struct spi_device {int dummy; } ;
struct s5c73m3 {struct spi_device* spi_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_DIR_RX ; 
 int spi_xmit (struct spi_device*,void*,unsigned int const,int /*<<< orphan*/ ) ; 

int s5c73m3_spi_read(struct s5c73m3 *state, void *addr,
		     const unsigned int len, const unsigned int tx_size)
{
	struct spi_device *spi_dev = state->spi_dev;
	u32 count = len / tx_size;
	u32 extra = len % tx_size;
	unsigned int i, j = 0;
	int r = 0;

	for (i = 0; i < count; i++) {
		r = spi_xmit(spi_dev, addr + j, tx_size, SPI_DIR_RX);
		if (r < 0)
			return r;
		j += tx_size;
	}

	if (extra > 0)
		return spi_xmit(spi_dev, addr + j, extra, SPI_DIR_RX);

	return 0;
}