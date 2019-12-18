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
typedef  size_t u8 ;
struct c2port_ops {size_t block_size; size_t blocks_num; } ;
struct c2port_device {struct c2port_ops* ops; } ;
typedef  size_t ssize_t ;
typedef  size_t loff_t ;

/* Variables and functions */
 size_t C2PORT_BLOCK_READ ; 
 size_t C2PORT_COMMAND_OK ; 
 int /*<<< orphan*/  C2PORT_FPDAT ; 
 size_t EBUSY ; 
 int c2port_poll_in_busy (struct c2port_device*) ; 
 int c2port_poll_out_ready (struct c2port_device*) ; 
 int c2port_read_dr (struct c2port_device*,...) ; 
 int /*<<< orphan*/  c2port_write_ar (struct c2port_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2port_write_dr (struct c2port_device*,size_t) ; 

__attribute__((used)) static ssize_t __c2port_read_flash_data(struct c2port_device *dev,
				char *buffer, loff_t offset, size_t count)
{
	struct c2port_ops *ops = dev->ops;
	u8 status, nread = 128;
	int i, ret;

	/* Check for flash end */
	if (offset >= ops->block_size * ops->blocks_num)
		return 0;

	if (ops->block_size * ops->blocks_num - offset < nread)
		nread = ops->block_size * ops->blocks_num - offset;
	if (count < nread)
		nread = count;
	if (nread == 0)
		return nread;

	/* Target the C2 flash programming data register for C2 data register
	 * access */
	c2port_write_ar(dev, C2PORT_FPDAT);

	/* Send flash block read command */
	c2port_write_dr(dev, C2PORT_BLOCK_READ);

	/* Wait for input acknowledge */
	ret = c2port_poll_in_busy(dev);
	if (ret < 0)
		return ret;

	/* Should check status before starting FLASH access sequence */

	/* Wait for status information */
	ret = c2port_poll_out_ready(dev);
	if (ret < 0)
		return ret;

	/* Read flash programming interface status */
	ret = c2port_read_dr(dev, &status);
	if (ret < 0)
		return ret;
	if (status != C2PORT_COMMAND_OK)
		return -EBUSY;

	/* Send address high byte */
	c2port_write_dr(dev, offset >> 8);
	ret = c2port_poll_in_busy(dev);
	if (ret < 0)
		return ret;

	/* Send address low byte */
	c2port_write_dr(dev, offset & 0x00ff);
	ret = c2port_poll_in_busy(dev);
	if (ret < 0)
		return ret;

	/* Send address block size */
	c2port_write_dr(dev, nread);
	ret = c2port_poll_in_busy(dev);
	if (ret < 0)
		return ret;

	/* Should check status before reading FLASH block */

	/* Wait for status information */
	ret = c2port_poll_out_ready(dev);
	if (ret < 0)
		return ret;

	/* Read flash programming interface status */
	ret = c2port_read_dr(dev, &status);
	if (ret < 0)
		return ret;
	if (status != C2PORT_COMMAND_OK)
		return -EBUSY;

	/* Read flash block */
	for (i = 0; i < nread; i++) {
		ret = c2port_poll_out_ready(dev);
		if (ret < 0)
			return ret;

		ret = c2port_read_dr(dev, buffer+i);
		if (ret < 0)
			return ret;
	}

	return nread;
}