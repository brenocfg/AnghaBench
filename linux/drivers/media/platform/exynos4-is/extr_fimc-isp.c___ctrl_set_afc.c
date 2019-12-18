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
 int /*<<< orphan*/  ISP_AFC_COMMAND_AUTO ; 
 int /*<<< orphan*/  ISP_AFC_COMMAND_DISABLE ; 
 int /*<<< orphan*/  ISP_AFC_COMMAND_MANUAL ; 
#define  V4L2_CID_POWER_LINE_FREQUENCY_50HZ 131 
#define  V4L2_CID_POWER_LINE_FREQUENCY_60HZ 130 
#define  V4L2_CID_POWER_LINE_FREQUENCY_AUTO 129 
#define  V4L2_CID_POWER_LINE_FREQUENCY_DISABLED 128 
 int /*<<< orphan*/  __is_set_isp_afc (struct fimc_is*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __ctrl_set_afc(struct fimc_is *is, int value)
{
	switch (value) {
	case V4L2_CID_POWER_LINE_FREQUENCY_DISABLED:
		__is_set_isp_afc(is, ISP_AFC_COMMAND_DISABLE, 0);
		break;
	case V4L2_CID_POWER_LINE_FREQUENCY_50HZ:
		__is_set_isp_afc(is, ISP_AFC_COMMAND_MANUAL, 50);
		break;
	case V4L2_CID_POWER_LINE_FREQUENCY_60HZ:
		__is_set_isp_afc(is, ISP_AFC_COMMAND_MANUAL, 60);
		break;
	case V4L2_CID_POWER_LINE_FREQUENCY_AUTO:
		__is_set_isp_afc(is, ISP_AFC_COMMAND_AUTO, 0);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}