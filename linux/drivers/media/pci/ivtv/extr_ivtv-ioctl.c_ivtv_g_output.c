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
struct ivtv {int v4l2_cap; unsigned int active_output; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct ivtv* itv; } ;

/* Variables and functions */
 int EINVAL ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 TYPE_1__* fh2id (void*) ; 

__attribute__((used)) static int ivtv_g_output(struct file *file, void *fh, unsigned int *i)
{
	struct ivtv *itv = fh2id(fh)->itv;

	if (!(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		return -EINVAL;

	*i = itv->active_output;

	return 0;
}