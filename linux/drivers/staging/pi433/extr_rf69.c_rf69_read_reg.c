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
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int spi_w8r8 (struct spi_device*,int) ; 

__attribute__((used)) static u8 rf69_read_reg(struct spi_device *spi, u8 addr)
{
	int retval;

	retval = spi_w8r8(spi, addr);

#ifdef DEBUG_VALUES
	if (retval < 0)
		/*
		 * should never happen, since we already checked,
		 * that module is connected. Therefore no error
		 * handling, just an optional error message...
		 */
		dev_dbg(&spi->dev, "read 0x%x FAILED\n", addr);
	else
		dev_dbg(&spi->dev, "read 0x%x from reg 0x%x\n", retval, addr);
#endif

	return retval;
}