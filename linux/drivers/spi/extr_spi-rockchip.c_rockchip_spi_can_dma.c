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
struct spi_transfer {int bits_per_word; unsigned int len; } ;
struct spi_master {int dummy; } ;
struct spi_device {int dummy; } ;
struct rockchip_spi {unsigned int fifo_len; } ;

/* Variables and functions */
 struct rockchip_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static bool rockchip_spi_can_dma(struct spi_master *master,
				 struct spi_device *spi,
				 struct spi_transfer *xfer)
{
	struct rockchip_spi *rs = spi_master_get_devdata(master);
	unsigned int bytes_per_word = xfer->bits_per_word <= 8 ? 1 : 2;

	/* if the numbor of spi words to transfer is less than the fifo
	 * length we can just fill the fifo and wait for a single irq,
	 * so don't bother setting up dma
	 */
	return xfer->len / bytes_per_word >= rs->fifo_len;
}