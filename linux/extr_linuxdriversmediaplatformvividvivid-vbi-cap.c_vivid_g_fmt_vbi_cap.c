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
struct vivid_dev {int std_cap; scalar_t__ vbi_cap_interlaced; } ;
struct v4l2_vbi_format {int sampling_rate; int offset; int samples_per_line; int* count; scalar_t__* reserved; int /*<<< orphan*/  flags; scalar_t__* start; int /*<<< orphan*/  sample_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_PIX_FMT_GREY ; 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  V4L2_VBI_INTERLACED ; 
 scalar_t__ V4L2_VBI_ITU_525_F1_START ; 
 scalar_t__ V4L2_VBI_ITU_525_F2_START ; 
 scalar_t__ V4L2_VBI_ITU_625_F1_START ; 
 scalar_t__ V4L2_VBI_ITU_625_F2_START ; 

__attribute__((used)) static void vivid_g_fmt_vbi_cap(struct vivid_dev *dev, struct v4l2_vbi_format *vbi)
{
	bool is_60hz = dev->std_cap & V4L2_STD_525_60;

	vbi->sampling_rate = 27000000;
	vbi->offset = 24;
	vbi->samples_per_line = 1440;
	vbi->sample_format = V4L2_PIX_FMT_GREY;
	vbi->start[0] = is_60hz ? V4L2_VBI_ITU_525_F1_START + 9 : V4L2_VBI_ITU_625_F1_START + 5;
	vbi->start[1] = is_60hz ? V4L2_VBI_ITU_525_F2_START + 9 : V4L2_VBI_ITU_625_F2_START + 5;
	vbi->count[0] = vbi->count[1] = is_60hz ? 12 : 18;
	vbi->flags = dev->vbi_cap_interlaced ? V4L2_VBI_INTERLACED : 0;
	vbi->reserved[0] = 0;
	vbi->reserved[1] = 0;
}