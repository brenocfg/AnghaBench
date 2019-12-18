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
struct v4l2_frequency {int /*<<< orphan*/  frequency; int /*<<< orphan*/  type; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct file {int dummy; } ;
struct av7110 {int current_input; int /*<<< orphan*/  current_freq; int /*<<< orphan*/  analog_tuner_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct v4l2_frequency*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_g_frequency(struct file *file, void *fh, struct v4l2_frequency *f)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct av7110 *av7110 = (struct av7110 *)dev->ext_priv;

	dprintk(2, "VIDIOC_G_FREQ: freq:0x%08x\n", f->frequency);

	if (!av7110->analog_tuner_flags || av7110->current_input != 1)
		return -EINVAL;

	memset(f, 0, sizeof(*f));
	f->type = V4L2_TUNER_ANALOG_TV;
	f->frequency =	av7110->current_freq;
	return 0;
}