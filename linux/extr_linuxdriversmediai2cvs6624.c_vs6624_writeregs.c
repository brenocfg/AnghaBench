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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vs6624_write (struct v4l2_subdev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vs6624_writeregs(struct v4l2_subdev *sd, const u16 *regs)
{
	u16 reg;
	u8 data;

	while (*regs != 0x00) {
		reg = *regs++;
		data = *regs++;

		vs6624_write(sd, reg, data);
	}
	return 0;
}