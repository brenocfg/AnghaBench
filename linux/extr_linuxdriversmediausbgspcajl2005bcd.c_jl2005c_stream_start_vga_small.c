#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int member_0; int member_1; } ;
typedef  TYPE_1__ u8 ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__**) ; 
 int jl2005c_write2 (struct gspca_dev*,TYPE_1__*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int jl2005c_stream_start_vga_small(struct gspca_dev *gspca_dev)
{
	int i;
	int retval = -1;
	static u8 instruction[][2] = {
		{0x06, 0x00},
		{0x7c, 0x00},
		{0x7d, 0x1a},
		{0x02, 0x00},
		{0x01, 0x00},
		{0x04, 0x52},
	};

	for (i = 0; i < ARRAY_SIZE(instruction); i++) {
		msleep(60);
		retval = jl2005c_write2(gspca_dev, instruction[i]);
		if (retval < 0)
			return retval;
	}
	msleep(60);
	return retval;
}