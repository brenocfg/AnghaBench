#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_fmtdesc {size_t index; scalar_t__ flags; int /*<<< orphan*/  pixelformat; } ;
struct file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pixelformat; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* sur40_pix_format ; 

__attribute__((used)) static int sur40_vidioc_enum_fmt(struct file *file, void *priv,
				 struct v4l2_fmtdesc *f)
{
	if (f->index >= ARRAY_SIZE(sur40_pix_format))
		return -EINVAL;

	f->pixelformat = sur40_pix_format[f->index].pixelformat;
	f->flags = 0;
	return 0;
}