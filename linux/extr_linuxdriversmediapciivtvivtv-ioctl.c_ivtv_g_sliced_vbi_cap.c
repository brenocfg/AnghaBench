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
struct v4l2_sliced_vbi_cap {scalar_t__ type; int** service_lines; int service_set; } ;
struct ivtv {int v4l2_cap; scalar_t__ is_60hz; scalar_t__ is_50hz; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct ivtv* itv; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_SLICED_VBI_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_SLICED_VBI_OUTPUT ; 
 int V4L2_CAP_SLICED_VBI_OUTPUT ; 
 void* V4L2_SLICED_CAPTION_525 ; 
 int V4L2_SLICED_VBI_525 ; 
 int V4L2_SLICED_VBI_625 ; 
 int V4L2_SLICED_VPS ; 
 int V4L2_SLICED_WSS_625 ; 
 TYPE_1__* fh2id (void*) ; 
 scalar_t__ valid_service_line (int,int,scalar_t__) ; 

__attribute__((used)) static int ivtv_g_sliced_vbi_cap(struct file *file, void *fh, struct v4l2_sliced_vbi_cap *cap)
{
	struct ivtv *itv = fh2id(fh)->itv;
	int set = itv->is_50hz ? V4L2_SLICED_VBI_625 : V4L2_SLICED_VBI_525;
	int f, l;

	if (cap->type == V4L2_BUF_TYPE_SLICED_VBI_CAPTURE) {
		for (f = 0; f < 2; f++) {
			for (l = 0; l < 24; l++) {
				if (valid_service_line(f, l, itv->is_50hz))
					cap->service_lines[f][l] = set;
			}
		}
	} else if (cap->type == V4L2_BUF_TYPE_SLICED_VBI_OUTPUT) {
		if (!(itv->v4l2_cap & V4L2_CAP_SLICED_VBI_OUTPUT))
			return -EINVAL;
		if (itv->is_60hz) {
			cap->service_lines[0][21] = V4L2_SLICED_CAPTION_525;
			cap->service_lines[1][21] = V4L2_SLICED_CAPTION_525;
		} else {
			cap->service_lines[0][23] = V4L2_SLICED_WSS_625;
			cap->service_lines[0][16] = V4L2_SLICED_VPS;
		}
	} else {
		return -EINVAL;
	}

	set = 0;
	for (f = 0; f < 2; f++)
		for (l = 0; l < 24; l++)
			set |= cap->service_lines[f][l];
	cap->service_set = set;
	return 0;
}