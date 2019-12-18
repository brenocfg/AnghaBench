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
struct v4l2_frequency {unsigned int frequency; scalar_t__ tuner; scalar_t__ type; } ;
struct tea5764_device {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int FREQ_MAX ; 
 int FREQ_MIN ; 
 int FREQ_MUL ; 
 scalar_t__ V4L2_TUNER_RADIO ; 
 unsigned int clamp (unsigned int,int,int) ; 
 int /*<<< orphan*/  tea5764_power_down (struct tea5764_device*) ; 
 int /*<<< orphan*/  tea5764_power_up (struct tea5764_device*) ; 
 int /*<<< orphan*/  tea5764_tune (struct tea5764_device*,unsigned int) ; 
 struct tea5764_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_frequency(struct file *file, void *priv,
				const struct v4l2_frequency *f)
{
	struct tea5764_device *radio = video_drvdata(file);
	unsigned freq = f->frequency;

	if (f->tuner != 0 || f->type != V4L2_TUNER_RADIO)
		return -EINVAL;
	if (freq == 0) {
		/* We special case this as a power down control. */
		tea5764_power_down(radio);
		/* Yes, that's what is returned in this case. This
		   whole special case is non-compliant and should really
		   be replaced with something better, but changing this
		   might well break code that depends on this behavior.
		   So we keep it as-is. */
		return -EINVAL;
	}
	freq = clamp(freq, FREQ_MIN * FREQ_MUL, FREQ_MAX * FREQ_MUL);
	tea5764_power_up(radio);
	tea5764_tune(radio, (freq * 125) / 2);
	return 0;
}