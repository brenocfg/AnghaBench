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
struct v4l2_fract {int numerator; int denominator; } ;
struct ivtv_open_id {struct ivtv* itv; } ;
struct ivtv {scalar_t__ is_out_50hz; scalar_t__ is_50hz; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 struct ivtv_open_id* fh2id (void*) ; 

__attribute__((used)) static int ivtv_g_pixelaspect(struct file *file, void *fh,
			      int type, struct v4l2_fract *f)
{
	struct ivtv_open_id *id = fh2id(fh);
	struct ivtv *itv = id->itv;

	if (type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		f->numerator = itv->is_50hz ? 54 : 11;
		f->denominator = itv->is_50hz ? 59 : 10;
	} else if (type == V4L2_BUF_TYPE_VIDEO_OUTPUT) {
		f->numerator = itv->is_out_50hz ? 54 : 11;
		f->denominator = itv->is_out_50hz ? 59 : 10;
	} else {
		return -EINVAL;
	}
	return 0;
}