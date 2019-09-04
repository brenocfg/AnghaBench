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
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 scalar_t__ write_reg (struct v4l2_subdev*,int const,int const) ; 

__attribute__((used)) static int write_regs(struct v4l2_subdev *sd, const u8 *regs)
{
	int i;

	for (i = 0; regs[i] != 0x00; i += 2)
		if (write_reg(sd, regs[i], regs[i + 1]) < 0)
			return -1;
	return 0;
}