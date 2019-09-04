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
typedef  unsigned char u8 ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int jl2005c_write2 (struct gspca_dev*,unsigned char*) ; 

__attribute__((used)) static int jl2005c_write_reg(struct gspca_dev *gspca_dev, unsigned char reg,
						    unsigned char value)
{
	int retval;
	u8 instruction[2];

	instruction[0] = reg;
	instruction[1] = value;

	retval = jl2005c_write2(gspca_dev, instruction);
	if (retval < 0)
			return retval;

	return retval;
}