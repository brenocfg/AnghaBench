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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_mbus_code_enum {scalar_t__ index; size_t pad; int code; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  S5C73M3_ISP_FMT 131 
#define  S5C73M3_ISP_PAD 130 
#define  S5C73M3_JPEG_FMT 129 
#define  S5C73M3_JPEG_PAD 128 
 size_t S5C73M3_NUM_PADS ; 

__attribute__((used)) static int s5c73m3_enum_mbus_code(struct v4l2_subdev *sd,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_mbus_code_enum *code)
{
	static const int codes[] = {
			[S5C73M3_ISP_PAD] = S5C73M3_ISP_FMT,
			[S5C73M3_JPEG_PAD] = S5C73M3_JPEG_FMT};

	if (code->index > 0 || code->pad >= S5C73M3_NUM_PADS)
		return -EINVAL;

	code->code = codes[code->pad];

	return 0;
}