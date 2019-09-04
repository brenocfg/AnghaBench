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
struct v4l2_fmtdesc {int index; int /*<<< orphan*/  pixelformat; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int EINVAL ; 
 int NUM_FORMATS ; 
 TYPE_1__* formats ; 

__attribute__((used)) static int vidioc_enum_fmt(struct file *file, void  *priv,
					struct v4l2_fmtdesc *f)
{
	int index = f->index;

	if (f->index >= NUM_FORMATS)
		return -EINVAL;

	f->pixelformat = formats[index].fourcc;
	return 0;
}