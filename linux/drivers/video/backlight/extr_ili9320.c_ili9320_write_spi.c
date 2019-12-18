#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ili9320_spi {unsigned char* buffer_addr; unsigned char* buffer_data; unsigned char id; int /*<<< orphan*/  message; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct ili9320_spi spi; } ;
struct ili9320 {TYPE_1__ access; } ;

/* Variables and functions */
 unsigned char ILI9320_SPI_DATA ; 
 unsigned char ILI9320_SPI_INDEX ; 
 unsigned char ILI9320_SPI_WRITE ; 
 int spi_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ili9320_write_spi(struct ili9320 *ili,
				    unsigned int reg,
				    unsigned int value)
{
	struct ili9320_spi *spi = &ili->access.spi;
	unsigned char *addr = spi->buffer_addr;
	unsigned char *data = spi->buffer_data;

	/* spi message consits of:
	 * first byte: ID and operation
	 */

	addr[0] = spi->id | ILI9320_SPI_INDEX | ILI9320_SPI_WRITE;
	addr[1] = reg >> 8;
	addr[2] = reg;

	/* second message is the data to transfer */

	data[0] = spi->id | ILI9320_SPI_DATA  | ILI9320_SPI_WRITE;
	data[1] = value >> 8;
	data[2] = value;

	return spi_sync(spi->dev, &spi->message);
}