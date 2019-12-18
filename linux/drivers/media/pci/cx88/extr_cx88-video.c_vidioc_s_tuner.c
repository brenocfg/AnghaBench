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
struct v4l2_tuner {scalar_t__ index; int /*<<< orphan*/  audmode; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ tuner_type; } ;
struct cx88_core {TYPE_1__ board; } ;
struct cx8800_dev {struct cx88_core* core; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ UNSET ; 
 int /*<<< orphan*/  cx88_set_stereo (struct cx88_core*,int /*<<< orphan*/ ,int) ; 
 struct cx8800_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_tuner(struct file *file, void *priv,
			  const struct v4l2_tuner *t)
{
	struct cx8800_dev *dev = video_drvdata(file);
	struct cx88_core *core = dev->core;

	if (core->board.tuner_type == UNSET)
		return -EINVAL;
	if (t->index != 0)
		return -EINVAL;

	cx88_set_stereo(core, t->audmode, 1);
	return 0;
}