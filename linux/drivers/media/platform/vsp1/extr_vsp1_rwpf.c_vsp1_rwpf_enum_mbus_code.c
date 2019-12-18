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
struct v4l2_subdev_mbus_code_enum {size_t index; unsigned int code; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (unsigned int const*) ; 
 int EINVAL ; 
#define  MEDIA_BUS_FMT_AHSV8888_1X32 130 
#define  MEDIA_BUS_FMT_ARGB8888_1X32 129 
#define  MEDIA_BUS_FMT_AYUV8_1X32 128 

__attribute__((used)) static int vsp1_rwpf_enum_mbus_code(struct v4l2_subdev *subdev,
				    struct v4l2_subdev_pad_config *cfg,
				    struct v4l2_subdev_mbus_code_enum *code)
{
	static const unsigned int codes[] = {
		MEDIA_BUS_FMT_ARGB8888_1X32,
		MEDIA_BUS_FMT_AHSV8888_1X32,
		MEDIA_BUS_FMT_AYUV8_1X32,
	};

	if (code->index >= ARRAY_SIZE(codes))
		return -EINVAL;

	code->code = codes[code->index];

	return 0;
}