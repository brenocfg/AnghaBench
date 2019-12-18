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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int cx231xx_read_i2c_data (struct cx231xx*,int,int /*<<< orphan*/ ,int,int*,int) ; 
 int cx231xx_write_i2c_data (struct cx231xx*,int,int /*<<< orphan*/ ,int,int,int) ; 

int cx231xx_reg_mask_write(struct cx231xx *dev, u8 dev_addr, u8 size,
			   u16 register_address, u8 bit_start, u8 bit_end,
			   u32 value)
{
	int status = 0;
	u32 tmp;
	u32 mask = 0;
	int i;

	if (bit_start > (size - 1) || bit_end > (size - 1))
		return -1;

	if (size == 8) {
		status =
		    cx231xx_read_i2c_data(dev, dev_addr, register_address, 2,
					  &tmp, 1);
	} else {
		status =
		    cx231xx_read_i2c_data(dev, dev_addr, register_address, 2,
					  &tmp, 4);
	}

	if (status < 0)
		return status;

	mask = 1 << bit_end;
	for (i = bit_end; i > bit_start && i > 0; i--)
		mask = mask + (1 << (i - 1));

	value <<= bit_start;

	if (size == 8) {
		tmp &= ~mask;
		tmp |= value;
		tmp &= 0xff;
		status =
		    cx231xx_write_i2c_data(dev, dev_addr, register_address, 2,
					   tmp, 1);
	} else {
		tmp &= ~mask;
		tmp |= value;
		status =
		    cx231xx_write_i2c_data(dev, dev_addr, register_address, 2,
					   tmp, 4);
	}

	return status;
}