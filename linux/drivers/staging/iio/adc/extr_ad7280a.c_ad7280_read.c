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
struct ad7280_state {unsigned int ctrl_hb; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7280A_CONTROL_HB ; 
 unsigned int AD7280A_CTRL_HB_CONV_INPUT_ALL ; 
 unsigned int AD7280A_CTRL_HB_CONV_RES_READ_ALL ; 
 unsigned int AD7280A_CTRL_HB_CONV_RES_READ_NO ; 
 unsigned int AD7280A_DEVADDR_MASTER ; 
 int /*<<< orphan*/  AD7280A_READ ; 
 int EFAULT ; 
 int EIO ; 
 int __ad7280_read32 (struct ad7280_state*,unsigned int*) ; 
 scalar_t__ ad7280_check_crc (struct ad7280_state*,unsigned int) ; 
 int ad7280_write (struct ad7280_state*,unsigned int,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int ad7280_read(struct ad7280_state *st, unsigned int devaddr,
		       unsigned int addr)
{
	int ret;
	unsigned int tmp;

	/* turns off the read operation on all parts */
	ret = ad7280_write(st, AD7280A_DEVADDR_MASTER, AD7280A_CONTROL_HB, 1,
			   AD7280A_CTRL_HB_CONV_INPUT_ALL |
			   AD7280A_CTRL_HB_CONV_RES_READ_NO |
			   st->ctrl_hb);
	if (ret)
		return ret;

	/* turns on the read operation on the addressed part */
	ret = ad7280_write(st, devaddr, AD7280A_CONTROL_HB, 0,
			   AD7280A_CTRL_HB_CONV_INPUT_ALL |
			   AD7280A_CTRL_HB_CONV_RES_READ_ALL |
			   st->ctrl_hb);
	if (ret)
		return ret;

	/* Set register address on the part to be read from */
	ret = ad7280_write(st, devaddr, AD7280A_READ, 0, addr << 2);
	if (ret)
		return ret;

	ret = __ad7280_read32(st, &tmp);
	if (ret)
		return ret;

	if (ad7280_check_crc(st, tmp))
		return -EIO;

	if (((tmp >> 27) != devaddr) || (((tmp >> 21) & 0x3F) != addr))
		return -EFAULT;

	return (tmp >> 13) & 0xFF;
}