#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int numerator; int denominator; } ;
struct v4l2_cropcap {scalar_t__ type; TYPE_1__ pixelaspect; } ;
struct file {int dummy; } ;
struct cx18 {scalar_t__ is_50hz; } ;
struct TYPE_4__ {struct cx18* cx; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 TYPE_2__* fh2id (void*) ; 

__attribute__((used)) static int cx18_cropcap(struct file *file, void *fh,
			struct v4l2_cropcap *cropcap)
{
	struct cx18 *cx = fh2id(fh)->cx;

	if (cropcap->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;
	cropcap->pixelaspect.numerator = cx->is_50hz ? 54 : 11;
	cropcap->pixelaspect.denominator = cx->is_50hz ? 59 : 10;
	return 0;
}