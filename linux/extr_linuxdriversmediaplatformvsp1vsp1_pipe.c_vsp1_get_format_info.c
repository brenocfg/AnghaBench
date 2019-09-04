#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vsp1_format_info {int fourcc; } ;
struct vsp1_device {TYPE_1__* info; } ;
struct TYPE_2__ {int gen; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct vsp1_format_info*) ; 
#define  V4L2_PIX_FMT_HSV24 130 
#define  V4L2_PIX_FMT_HSV32 129 
#define  V4L2_PIX_FMT_VYUY 128 
 struct vsp1_format_info* vsp1_video_formats ; 

const struct vsp1_format_info *vsp1_get_format_info(struct vsp1_device *vsp1,
						    u32 fourcc)
{
	unsigned int i;

	/* Special case, the VYUY and HSV formats are supported on Gen2 only. */
	if (vsp1->info->gen != 2) {
		switch (fourcc) {
		case V4L2_PIX_FMT_VYUY:
		case V4L2_PIX_FMT_HSV24:
		case V4L2_PIX_FMT_HSV32:
			return NULL;
		}
	}

	for (i = 0; i < ARRAY_SIZE(vsp1_video_formats); ++i) {
		const struct vsp1_format_info *info = &vsp1_video_formats[i];

		if (info->fourcc == fourcc)
			return info;
	}

	return NULL;
}