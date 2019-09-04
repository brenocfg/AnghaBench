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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum rmi_f54_report_type { ____Placeholder_rmi_f54_report_type } rmi_f54_report_type ;

/* Variables and functions */
 int EINVAL ; 
#define  F54_16BIT_IMAGE 135 
#define  F54_8BIT_IMAGE 134 
#define  F54_FULL_RAW_CAP 133 
#define  F54_FULL_RAW_CAP_RX_OFFSET_REMOVED 132 
#define  F54_MAX_REPORT_TYPE 131 
#define  F54_RAW_16BIT_IMAGE 130 
#define  F54_REPORT_NONE 129 
#define  F54_TRUE_BASELINE 128 
 int /*<<< orphan*/  V4L2_TCH_FMT_DELTA_TD08 ; 
 int /*<<< orphan*/  V4L2_TCH_FMT_DELTA_TD16 ; 
 int /*<<< orphan*/  V4L2_TCH_FMT_TU16 ; 

__attribute__((used)) static int rmi_f54_get_pixel_fmt(enum rmi_f54_report_type reptype, u32 *pixfmt)
{
	int ret = 0;

	switch (reptype) {
	case F54_8BIT_IMAGE:
		*pixfmt = V4L2_TCH_FMT_DELTA_TD08;
		break;

	case F54_16BIT_IMAGE:
		*pixfmt = V4L2_TCH_FMT_DELTA_TD16;
		break;

	case F54_RAW_16BIT_IMAGE:
	case F54_TRUE_BASELINE:
	case F54_FULL_RAW_CAP:
	case F54_FULL_RAW_CAP_RX_OFFSET_REMOVED:
		*pixfmt = V4L2_TCH_FMT_TU16;
		break;

	case F54_REPORT_NONE:
	case F54_MAX_REPORT_TYPE:
		ret = -EINVAL;
		break;
	}

	return ret;
}