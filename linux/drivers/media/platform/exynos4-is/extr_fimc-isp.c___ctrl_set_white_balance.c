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
struct fimc_is {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ISP_AWB_COMMAND_AUTO ; 
 int /*<<< orphan*/  ISP_AWB_COMMAND_ILLUMINATION ; 
 int /*<<< orphan*/  ISP_AWB_ILLUMINATION_CLOUDY ; 
 int /*<<< orphan*/  ISP_AWB_ILLUMINATION_DAYLIGHT ; 
 int /*<<< orphan*/  ISP_AWB_ILLUMINATION_FLUORESCENT ; 
 int /*<<< orphan*/  ISP_AWB_ILLUMINATION_TUNGSTEN ; 
#define  V4L2_WHITE_BALANCE_AUTO 132 
#define  V4L2_WHITE_BALANCE_CLOUDY 131 
#define  V4L2_WHITE_BALANCE_DAYLIGHT 130 
#define  V4L2_WHITE_BALANCE_FLUORESCENT 129 
#define  V4L2_WHITE_BALANCE_INCANDESCENT 128 
 int /*<<< orphan*/  __is_set_isp_awb (struct fimc_is*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ctrl_set_white_balance(struct fimc_is *is, int value)
{
	switch (value) {
	case V4L2_WHITE_BALANCE_AUTO:
		__is_set_isp_awb(is, ISP_AWB_COMMAND_AUTO, 0);
		break;
	case V4L2_WHITE_BALANCE_DAYLIGHT:
		__is_set_isp_awb(is, ISP_AWB_COMMAND_ILLUMINATION,
					ISP_AWB_ILLUMINATION_DAYLIGHT);
		break;
	case V4L2_WHITE_BALANCE_CLOUDY:
		__is_set_isp_awb(is, ISP_AWB_COMMAND_ILLUMINATION,
					ISP_AWB_ILLUMINATION_CLOUDY);
		break;
	case V4L2_WHITE_BALANCE_INCANDESCENT:
		__is_set_isp_awb(is, ISP_AWB_COMMAND_ILLUMINATION,
					ISP_AWB_ILLUMINATION_TUNGSTEN);
		break;
	case V4L2_WHITE_BALANCE_FLUORESCENT:
		__is_set_isp_awb(is, ISP_AWB_COMMAND_ILLUMINATION,
					ISP_AWB_ILLUMINATION_FLUORESCENT);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}