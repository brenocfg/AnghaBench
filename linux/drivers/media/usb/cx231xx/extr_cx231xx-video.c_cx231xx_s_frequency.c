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
typedef  int u32 ;
typedef  struct v4l2_frequency {int frequency; scalar_t__ tuner; int /*<<< orphan*/  type; } const v4l2_frequency ;
struct file {int dummy; } ;
struct cx231xx_fh {struct cx231xx* dev; } ;
struct cx231xx {int ctl_freq; scalar_t__ tuner_type; int norm; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TUNER_NXP_TDA18271 ; 
 int V4L2_STD_B ; 
 int V4L2_STD_GH ; 
 int V4L2_STD_MN ; 
 int V4L2_STD_NTSC_443 ; 
 int V4L2_STD_PAL_DK ; 
 int V4L2_STD_PAL_I ; 
 int V4L2_STD_SECAM_DK ; 
 int V4L2_STD_SECAM_L ; 
 int V4L2_STD_SECAM_LC ; 
 int /*<<< orphan*/  call_all (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_frequency const*) ; 
 int check_dev (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_set_Colibri_For_LowIF (struct cx231xx*,int,int,int) ; 
 int cx231xx_tuner_post_channel_change (struct cx231xx*) ; 
 int cx231xx_tuner_pre_channel_change (struct cx231xx*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  g_frequency ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  tuner ; 
 int /*<<< orphan*/  update_HH_register_after_set_DIF (struct cx231xx*) ; 

int cx231xx_s_frequency(struct file *file, void *priv,
			      const struct v4l2_frequency *f)
{
	struct cx231xx_fh *fh = priv;
	struct cx231xx *dev = fh->dev;
	struct v4l2_frequency new_freq = *f;
	int rc;
	u32 if_frequency = 5400000;

	dev_dbg(dev->dev,
		"Enter vidioc_s_frequency()f->frequency=%d;f->type=%d\n",
		f->frequency, f->type);

	rc = check_dev(dev);
	if (rc < 0)
		return rc;

	if (0 != f->tuner)
		return -EINVAL;

	/* set pre channel change settings in DIF first */
	rc = cx231xx_tuner_pre_channel_change(dev);

	call_all(dev, tuner, s_frequency, f);
	call_all(dev, tuner, g_frequency, &new_freq);
	dev->ctl_freq = new_freq.frequency;

	/* set post channel change settings in DIF first */
	rc = cx231xx_tuner_post_channel_change(dev);

	if (dev->tuner_type == TUNER_NXP_TDA18271) {
		if (dev->norm & (V4L2_STD_MN | V4L2_STD_NTSC_443))
			if_frequency = 5400000;  /*5.4MHz	*/
		else if (dev->norm & V4L2_STD_B)
			if_frequency = 6000000;  /*6.0MHz	*/
		else if (dev->norm & (V4L2_STD_PAL_DK | V4L2_STD_SECAM_DK))
			if_frequency = 6900000;  /*6.9MHz	*/
		else if (dev->norm & V4L2_STD_GH)
			if_frequency = 7100000;  /*7.1MHz	*/
		else if (dev->norm & V4L2_STD_PAL_I)
			if_frequency = 7250000;  /*7.25MHz	*/
		else if (dev->norm & V4L2_STD_SECAM_L)
			if_frequency = 6900000;  /*6.9MHz	*/
		else if (dev->norm & V4L2_STD_SECAM_LC)
			if_frequency = 1250000;  /*1.25MHz	*/

		dev_dbg(dev->dev,
			"if_frequency is set to %d\n", if_frequency);
		cx231xx_set_Colibri_For_LowIF(dev, if_frequency, 1, 1);

		update_HH_register_after_set_DIF(dev);
	}

	dev_dbg(dev->dev, "Set New FREQUENCY to %d\n", f->frequency);

	return rc;
}