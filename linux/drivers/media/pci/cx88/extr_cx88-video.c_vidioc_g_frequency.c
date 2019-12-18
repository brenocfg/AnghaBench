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
struct v4l2_frequency {int /*<<< orphan*/  frequency; scalar_t__ tuner; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ tuner_type; } ;
struct cx88_core {int /*<<< orphan*/  freq; TYPE_1__ board; } ;
struct cx8800_dev {struct cx88_core* core; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ UNSET ; 
 int /*<<< orphan*/  call_all (struct cx88_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency*) ; 
 int /*<<< orphan*/  g_frequency ; 
 int /*<<< orphan*/  tuner ; 
 scalar_t__ unlikely (int) ; 
 struct cx8800_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_frequency(struct file *file, void *priv,
			      struct v4l2_frequency *f)
{
	struct cx8800_dev *dev = video_drvdata(file);
	struct cx88_core *core = dev->core;

	if (unlikely(core->board.tuner_type == UNSET))
		return -EINVAL;
	if (f->tuner)
		return -EINVAL;

	f->frequency = core->freq;

	call_all(core, tuner, g_frequency, f);

	return 0;
}