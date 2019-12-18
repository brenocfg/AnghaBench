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
struct v4l2_input {int index; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct file {int dummy; } ;
struct av7110 {scalar_t__ analog_tuner_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (int,char*,int) ; 
 int /*<<< orphan*/ * inputs ; 
 int /*<<< orphan*/  memcpy (struct v4l2_input*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vidioc_enum_input(struct file *file, void *fh, struct v4l2_input *i)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct av7110 *av7110 = (struct av7110 *)dev->ext_priv;

	dprintk(2, "VIDIOC_ENUMINPUT: %d\n", i->index);

	if (av7110->analog_tuner_flags) {
		if (i->index >= 4)
			return -EINVAL;
	} else {
		if (i->index != 0)
			return -EINVAL;
	}

	memcpy(i, &inputs[i->index], sizeof(struct v4l2_input));

	return 0;
}