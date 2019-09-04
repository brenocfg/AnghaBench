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
struct v4l2_frequency {scalar_t__ tuner; unsigned int frequency; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

int vivid_radio_g_frequency(struct file *file, const unsigned *pfreq, struct v4l2_frequency *vf)
{
	if (vf->tuner != 0)
		return -EINVAL;
	vf->frequency = *pfreq;
	return 0;
}