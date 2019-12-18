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
typedef  int u32 ;
struct sun6i_csi_dev {int /*<<< orphan*/  dev; } ;
typedef  enum csi_input_fmt { ____Placeholder_csi_input_fmt } csi_input_fmt ;

/* Variables and functions */
 int CSI_INPUT_FORMAT_RAW ; 
 int CSI_INPUT_FORMAT_YUV422 ; 
#define  V4L2_PIX_FMT_UYVY 131 
#define  V4L2_PIX_FMT_VYUY 130 
#define  V4L2_PIX_FMT_YUYV 129 
#define  V4L2_PIX_FMT_YVYU 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum csi_input_fmt get_csi_input_format(struct sun6i_csi_dev *sdev,
					       u32 mbus_code, u32 pixformat)
{
	/* non-YUV */
	if ((mbus_code & 0xF000) != 0x2000)
		return CSI_INPUT_FORMAT_RAW;

	switch (pixformat) {
	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_YVYU:
	case V4L2_PIX_FMT_UYVY:
	case V4L2_PIX_FMT_VYUY:
		return CSI_INPUT_FORMAT_RAW;
	default:
		break;
	}

	/* not support YUV420 input format yet */
	dev_dbg(sdev->dev, "Select YUV422 as default input format of CSI.\n");
	return CSI_INPUT_FORMAT_YUV422;
}