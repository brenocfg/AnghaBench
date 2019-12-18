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
typedef  int u32 ;
struct v4l2_tuner {scalar_t__ index; int rangehigh; int signal; int /*<<< orphan*/  capability; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ tuner_type; } ;
struct cx88_core {TYPE_1__ board; } ;
struct cx8802_dev {struct cx88_core* core; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MO_DEVICE_STATUS ; 
 scalar_t__ UNSET ; 
 int /*<<< orphan*/  V4L2_TUNER_CAP_NORM ; 
 int /*<<< orphan*/  call_all (struct cx88_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_tuner*) ; 
 int /*<<< orphan*/  cx88_get_stereo (struct cx88_core*,struct v4l2_tuner*) ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_tuner ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tuner ; 
 scalar_t__ unlikely (int) ; 
 struct cx8802_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_tuner(struct file *file, void *priv,
			  struct v4l2_tuner *t)
{
	struct cx8802_dev *dev = video_drvdata(file);
	struct cx88_core *core = dev->core;
	u32 reg;

	if (unlikely(core->board.tuner_type == UNSET))
		return -EINVAL;
	if (t->index != 0)
		return -EINVAL;

	strscpy(t->name, "Television", sizeof(t->name));
	t->capability = V4L2_TUNER_CAP_NORM;
	t->rangehigh  = 0xffffffffUL;
	call_all(core, tuner, g_tuner, t);

	cx88_get_stereo(core, t);
	reg = cx_read(MO_DEVICE_STATUS);
	t->signal = (reg & (1 << 5)) ? 0xffff : 0x0000;
	return 0;
}