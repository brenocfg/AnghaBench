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
 int EINVAL ; 
 int /*<<< orphan*/  MASK_FIFO_THRESH_VALUE ; 
 int /*<<< orphan*/  REG_FIFO_THRESH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int rf69_read_fifo (struct spi_device*,int*,int) ; 
 int rf69_read_mod_write (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int rf69_set_fifo_threshold(struct spi_device *spi, u8 threshold)
{
	int retval;

	/* check input value */
	if (threshold & 0x80) {
		dev_dbg(&spi->dev, "set: illegal input param");
		return -EINVAL;
	}

	/* write value */
	retval = rf69_read_mod_write(spi, REG_FIFO_THRESH,
				     MASK_FIFO_THRESH_VALUE,
				     threshold);
	if (retval)
		return retval;

	/*
	 * access the fifo to activate new threshold
	 * retval (mis-) used as buffer here
	 */
	return rf69_read_fifo(spi, (u8 *)&retval, 1);
}