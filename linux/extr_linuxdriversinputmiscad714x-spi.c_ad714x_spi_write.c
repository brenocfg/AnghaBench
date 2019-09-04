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
typedef  int /*<<< orphan*/  u8 ;
struct spi_device {int dummy; } ;
struct ad714x_chip {int /*<<< orphan*/  dev; void** xfer_buf; } ;

/* Variables and functions */
 unsigned short AD714x_SPI_CMD_PREFIX ; 
 void* cpu_to_be16 (unsigned short) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int spi_write (struct spi_device*,int /*<<< orphan*/ *,int) ; 
 struct spi_device* to_spi_device (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ad714x_spi_write(struct ad714x_chip *chip,
			    unsigned short reg, unsigned short data)
{
	struct spi_device *spi = to_spi_device(chip->dev);
	int error;

	chip->xfer_buf[0] = cpu_to_be16(AD714x_SPI_CMD_PREFIX | reg);
	chip->xfer_buf[1] = cpu_to_be16(data);

	error = spi_write(spi, (u8 *)chip->xfer_buf,
			  2 * sizeof(*chip->xfer_buf));
	if (unlikely(error)) {
		dev_err(chip->dev, "SPI write error: %d\n", error);
		return error;
	}

	return 0;
}