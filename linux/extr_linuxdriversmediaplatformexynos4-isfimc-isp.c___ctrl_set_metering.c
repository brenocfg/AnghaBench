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
 unsigned int ISP_METERING_COMMAND_AVERAGE ; 
 unsigned int ISP_METERING_COMMAND_CENTER ; 
 unsigned int ISP_METERING_COMMAND_MATRIX ; 
 unsigned int ISP_METERING_COMMAND_SPOT ; 
 int /*<<< orphan*/  IS_METERING_CONFIG_CMD ; 
#define  V4L2_EXPOSURE_METERING_AVERAGE 131 
#define  V4L2_EXPOSURE_METERING_CENTER_WEIGHTED 130 
#define  V4L2_EXPOSURE_METERING_MATRIX 129 
#define  V4L2_EXPOSURE_METERING_SPOT 128 
 int /*<<< orphan*/  __is_set_isp_metering (struct fimc_is*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int __ctrl_set_metering(struct fimc_is *is, unsigned int value)
{
	unsigned int val;

	switch (value) {
	case V4L2_EXPOSURE_METERING_AVERAGE:
		val = ISP_METERING_COMMAND_AVERAGE;
		break;
	case V4L2_EXPOSURE_METERING_CENTER_WEIGHTED:
		val = ISP_METERING_COMMAND_CENTER;
		break;
	case V4L2_EXPOSURE_METERING_SPOT:
		val = ISP_METERING_COMMAND_SPOT;
		break;
	case V4L2_EXPOSURE_METERING_MATRIX:
		val = ISP_METERING_COMMAND_MATRIX;
		break;
	default:
		return -EINVAL;
	}

	__is_set_isp_metering(is, IS_METERING_CONFIG_CMD, val);
	return 0;
}