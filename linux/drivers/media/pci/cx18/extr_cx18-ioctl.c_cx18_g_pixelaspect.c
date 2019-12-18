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
struct v4l2_fract {int numerator; int denominator; } ;
struct file {int dummy; } ;
struct cx18 {scalar_t__ is_50hz; } ;
struct TYPE_2__ {struct cx18* cx; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 TYPE_1__* fh2id (void*) ; 

__attribute__((used)) static int cx18_g_pixelaspect(struct file *file, void *fh,
			      int type, struct v4l2_fract *f)
{
	struct cx18 *cx = fh2id(fh)->cx;

	if (type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	f->numerator = cx->is_50hz ? 54 : 11;
	f->denominator = cx->is_50hz ? 59 : 10;
	return 0;
}