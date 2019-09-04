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
struct v4l2_subdev {int dummy; } ;
struct m5mols_info {struct v4l2_subdev sd; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned short const**) ; 
 int /*<<< orphan*/  AWB_MANUAL ; 
 int /*<<< orphan*/  AWB_MODE ; 
 int EINVAL ; 
#define  REG_AWB_AUTO 145 
#define  REG_AWB_CLOUDY 144 
#define  REG_AWB_DAYLIGHT 143 
#define  REG_AWB_FLUORESCENT_1 142 
#define  REG_AWB_FLUORESCENT_2 141 
#define  REG_AWB_HORIZON 140 
#define  REG_AWB_INCANDESCENT 139 
#define  REG_AWB_LEDLIGHT 138 
 unsigned short const REG_AWB_PRESET ; 
#define  REG_AWB_SHADE 137 
#define  V4L2_WHITE_BALANCE_AUTO 136 
#define  V4L2_WHITE_BALANCE_CLOUDY 135 
#define  V4L2_WHITE_BALANCE_DAYLIGHT 134 
#define  V4L2_WHITE_BALANCE_FLASH 133 
#define  V4L2_WHITE_BALANCE_FLUORESCENT 132 
#define  V4L2_WHITE_BALANCE_FLUORESCENT_H 131 
#define  V4L2_WHITE_BALANCE_HORIZON 130 
#define  V4L2_WHITE_BALANCE_INCANDESCENT 129 
#define  V4L2_WHITE_BALANCE_SHADE 128 
 int /*<<< orphan*/  m5mols_debug ; 
 int m5mols_write (struct v4l2_subdev*,int /*<<< orphan*/ ,unsigned short const) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,unsigned short const) ; 

__attribute__((used)) static int m5mols_set_white_balance(struct m5mols_info *info, int val)
{
	static const unsigned short wb[][2] = {
		{ V4L2_WHITE_BALANCE_INCANDESCENT,  REG_AWB_INCANDESCENT },
		{ V4L2_WHITE_BALANCE_FLUORESCENT,   REG_AWB_FLUORESCENT_1 },
		{ V4L2_WHITE_BALANCE_FLUORESCENT_H, REG_AWB_FLUORESCENT_2 },
		{ V4L2_WHITE_BALANCE_HORIZON,       REG_AWB_HORIZON },
		{ V4L2_WHITE_BALANCE_DAYLIGHT,      REG_AWB_DAYLIGHT },
		{ V4L2_WHITE_BALANCE_FLASH,         REG_AWB_LEDLIGHT },
		{ V4L2_WHITE_BALANCE_CLOUDY,        REG_AWB_CLOUDY },
		{ V4L2_WHITE_BALANCE_SHADE,         REG_AWB_SHADE },
		{ V4L2_WHITE_BALANCE_AUTO,          REG_AWB_AUTO },
	};
	int i;
	struct v4l2_subdev *sd = &info->sd;
	int ret = -EINVAL;

	for (i = 0; i < ARRAY_SIZE(wb); i++) {
		int awb;
		if (wb[i][0] != val)
			continue;

		v4l2_dbg(1, m5mols_debug, sd,
			 "Setting white balance to: %#x\n", wb[i][0]);

		awb = wb[i][0] == V4L2_WHITE_BALANCE_AUTO;
		ret = m5mols_write(sd, AWB_MODE, awb ? REG_AWB_AUTO :
						 REG_AWB_PRESET);
		if (ret < 0)
			return ret;

		if (!awb)
			ret = m5mols_write(sd, AWB_MANUAL, wb[i][1]);
	}

	return ret;
}