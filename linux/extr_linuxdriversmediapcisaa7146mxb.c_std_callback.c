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
typedef  int v4l2_std_id ;
struct saa7146_standard {scalar_t__ id; } ;
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct mxb {scalar_t__ cur_input; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_D (char*) ; 
 int /*<<< orphan*/  GPIO_CTRL ; 
 int V4L2_STD_PAL_BG ; 
 scalar_t__ V4L2_STD_PAL_I ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  s_gpio ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  saa7111a_call (struct mxb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  saa7146_write (struct saa7146_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tuner_call (struct mxb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int std_callback(struct saa7146_dev *dev, struct saa7146_standard *standard)
{
	struct mxb *mxb = (struct mxb *)dev->ext_priv;

	if (V4L2_STD_PAL_I == standard->id) {
		v4l2_std_id std = V4L2_STD_PAL_I;

		DEB_D("VIDIOC_S_STD: setting mxb for PAL_I\n");
		/* These two gpio calls set the GPIO pins that control the tda9820 */
		saa7146_write(dev, GPIO_CTRL, 0x00404050);
		saa7111a_call(mxb, core, s_gpio, 0);
		saa7111a_call(mxb, video, s_std, std);
		if (mxb->cur_input == 0)
			tuner_call(mxb, video, s_std, std);
	} else {
		v4l2_std_id std = V4L2_STD_PAL_BG;

		if (mxb->cur_input)
			std = standard->id;
		DEB_D("VIDIOC_S_STD: setting mxb for PAL/NTSC/SECAM\n");
		/* These two gpio calls set the GPIO pins that control the tda9820 */
		saa7146_write(dev, GPIO_CTRL, 0x00404050);
		saa7111a_call(mxb, core, s_gpio, 1);
		saa7111a_call(mxb, video, s_std, std);
		if (mxb->cur_input == 0)
			tuner_call(mxb, video, s_std, std);
	}
	return 0;
}