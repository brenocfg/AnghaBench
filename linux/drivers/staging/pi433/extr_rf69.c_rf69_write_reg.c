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
typedef  char u8 ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 char WRITE_BIT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char,char) ; 
 int spi_write (struct spi_device*,char**,int) ; 

__attribute__((used)) static int rf69_write_reg(struct spi_device *spi, u8 addr, u8 value)
{
	int retval;
	char buffer[2];

	buffer[0] = addr | WRITE_BIT;
	buffer[1] = value;

	retval = spi_write(spi, &buffer, 2);

#ifdef DEBUG_VALUES
	if (retval < 0)
		/*
		 * should never happen, since we already checked,
		 * that module is connected. Therefore no error
		 * handling, just an optional error message...
		 */
		dev_dbg(&spi->dev, "write 0x%x to 0x%x FAILED\n", value, addr);
	else
		dev_dbg(&spi->dev, "wrote 0x%x to reg 0x%x\n", value, addr);
#endif

	return retval;
}