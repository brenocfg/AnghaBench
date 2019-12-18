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
struct v4l2_audio {scalar_t__ index; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct file {int dummy; } ;
struct av7110 {int current_input; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (int,char*,scalar_t__) ; 

__attribute__((used)) static int vidioc_s_audio(struct file *file, void *fh, const struct v4l2_audio *a)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct av7110 *av7110 = (struct av7110 *)dev->ext_priv;

	dprintk(2, "VIDIOC_S_AUDIO: %d\n", a->index);
	if (av7110->current_input >= 2)
		return -EINVAL;
	return a->index ? -EINVAL : 0;
}