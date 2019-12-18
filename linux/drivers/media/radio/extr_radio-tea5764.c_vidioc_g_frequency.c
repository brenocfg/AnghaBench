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
struct v4l2_frequency {scalar_t__ tuner; int frequency; int /*<<< orphan*/  type; } ;
struct tea5764_regs {int tnctrl; } ;
struct tea5764_device {struct tea5764_regs regs; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int TEA5764_TNCTRL_PUPD0 ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 int tea5764_get_freq (struct tea5764_device*) ; 
 int /*<<< orphan*/  tea5764_i2c_read (struct tea5764_device*) ; 
 struct tea5764_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_frequency(struct file *file, void *priv,
				struct v4l2_frequency *f)
{
	struct tea5764_device *radio = video_drvdata(file);
	struct tea5764_regs *r = &radio->regs;

	if (f->tuner != 0)
		return -EINVAL;
	tea5764_i2c_read(radio);
	f->type = V4L2_TUNER_RADIO;
	if (r->tnctrl & TEA5764_TNCTRL_PUPD0)
		f->frequency = (tea5764_get_freq(radio) * 2) / 125;
	else
		f->frequency = 0;

	return 0;
}