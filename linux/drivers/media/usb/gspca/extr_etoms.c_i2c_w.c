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
struct gspca_dev {int dummy; } ;
typedef  int __u8 ;

/* Variables and functions */
 scalar_t__ ET_I2C_BASE ; 
 scalar_t__ ET_I2C_COUNT ; 
 scalar_t__ ET_I2C_DATA0 ; 
 scalar_t__ ET_I2C_REG ; 
 int /*<<< orphan*/  reg_w_val (struct gspca_dev*,scalar_t__,int const) ; 

__attribute__((used)) static int i2c_w(struct gspca_dev *gspca_dev,
		 __u8 reg,
		 const __u8 *buffer,
		 int len, __u8 mode)
{
	/* buffer should be [D0..D7] */
	__u8 ptchcount;

	/* set the base address */
	reg_w_val(gspca_dev, ET_I2C_BASE, 0x40);
					 /* sensor base for the pas106 */
	/* set count and prefetch */
	ptchcount = ((len & 0x07) << 4) | (mode & 0x03);
	reg_w_val(gspca_dev, ET_I2C_COUNT, ptchcount);
	/* set the register base */
	reg_w_val(gspca_dev, ET_I2C_REG, reg);
	while (--len >= 0)
		reg_w_val(gspca_dev, ET_I2C_DATA0 + len, buffer[len]);
	return 0;
}