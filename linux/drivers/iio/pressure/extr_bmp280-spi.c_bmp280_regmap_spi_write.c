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
struct spi_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,void const*,int) ; 
 int spi_write_then_read (struct spi_device*,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int bmp280_regmap_spi_write(void *context, const void *data,
                                   size_t count)
{
	struct device *dev = context;
	struct spi_device *spi = to_spi_device(dev);
	u8 buf[2];

	memcpy(buf, data, 2);
	/*
	 * The SPI register address (= full register address without bit 7) and
	 * the write command (bit7 = RW = '0')
	 */
	buf[0] &= ~0x80;

	return spi_write_then_read(spi, buf, 2, NULL, 0);
}