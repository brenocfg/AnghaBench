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
struct v4l2_frequency {scalar_t__ tuner; int /*<<< orphan*/  frequency; } ;
struct file {int dummy; } ;
struct em28xx_v4l2 {int /*<<< orphan*/  frequency; } ;
struct em28xx {struct em28xx_v4l2* v4l2; } ;

/* Variables and functions */
 int EINVAL ; 
 struct em28xx* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_frequency(struct file *file, void *priv,
			      struct v4l2_frequency *f)
{
	struct em28xx         *dev = video_drvdata(file);
	struct em28xx_v4l2    *v4l2 = dev->v4l2;

	if (f->tuner != 0)
		return -EINVAL;

	f->frequency = v4l2->frequency;
	return 0;
}