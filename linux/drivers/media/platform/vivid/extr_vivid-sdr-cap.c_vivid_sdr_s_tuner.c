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
struct v4l2_tuner {int index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

int vivid_sdr_s_tuner(struct file *file, void *fh, const struct v4l2_tuner *vt)
{
	if (vt->index > 1)
		return -EINVAL;
	return 0;
}