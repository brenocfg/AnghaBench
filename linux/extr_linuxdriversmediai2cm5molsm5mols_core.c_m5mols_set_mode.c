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
typedef  scalar_t__ u8 ;
struct v4l2_subdev {int dummy; } ;
struct m5mols_info {scalar_t__ mode; struct v4l2_subdev sd; } ;

/* Variables and functions */
 int EINVAL ; 
#define  REG_CAPTURE 130 
#define  REG_MONITOR 129 
#define  REG_PARAMETER 128 
 int /*<<< orphan*/  SYSTEM_SYSMODE ; 
 int m5mols_read_u8 (struct v4l2_subdev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int m5mols_reg_mode (struct v4l2_subdev*,scalar_t__ const) ; 
 int /*<<< orphan*/  v4l2_warn (struct v4l2_subdev*,char*,scalar_t__) ; 

int m5mols_set_mode(struct m5mols_info *info, u8 mode)
{
	struct v4l2_subdev *sd = &info->sd;
	int ret = -EINVAL;
	u8 reg;

	if (mode < REG_PARAMETER || mode > REG_CAPTURE)
		return ret;

	ret = m5mols_read_u8(sd, SYSTEM_SYSMODE, &reg);
	if (ret || reg == mode)
		return ret;

	switch (reg) {
	case REG_PARAMETER:
		ret = m5mols_reg_mode(sd, REG_MONITOR);
		if (mode == REG_MONITOR)
			break;
		if (!ret)
			ret = m5mols_reg_mode(sd, REG_CAPTURE);
		break;

	case REG_MONITOR:
		if (mode == REG_PARAMETER) {
			ret = m5mols_reg_mode(sd, REG_PARAMETER);
			break;
		}

		ret = m5mols_reg_mode(sd, REG_CAPTURE);
		break;

	case REG_CAPTURE:
		ret = m5mols_reg_mode(sd, REG_MONITOR);
		if (mode == REG_MONITOR)
			break;
		if (!ret)
			ret = m5mols_reg_mode(sd, REG_PARAMETER);
		break;

	default:
		v4l2_warn(sd, "Wrong mode: %d\n", mode);
	}

	if (!ret)
		info->mode = mode;

	return ret;
}