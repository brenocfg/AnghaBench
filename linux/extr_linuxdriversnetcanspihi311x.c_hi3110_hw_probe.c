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
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HI3110_READ_STATF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hi3110_hw_reset (struct spi_device*) ; 
 int hi3110_read (struct spi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hi3110_hw_probe(struct spi_device *spi)
{
	u8 statf;

	hi3110_hw_reset(spi);

	/* Confirm correct operation by checking against reset values
	 * in datasheet
	 */
	statf = hi3110_read(spi, HI3110_READ_STATF);

	dev_dbg(&spi->dev, "statf: %02X\n", statf);

	if (statf != 0x82)
		return -ENODEV;

	return 0;
}