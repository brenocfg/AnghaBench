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
struct file {int dummy; } ;
struct cx25821_dev {int tvnorm; } ;
struct cx25821_channel {int width; int height; struct cx25821_dev* dev; } ;

/* Variables and functions */
 int V4L2_STD_625_50 ; 
 int /*<<< orphan*/  medusa_set_videostandard (struct cx25821_dev*) ; 
 struct cx25821_channel* video_drvdata (struct file*) ; 

__attribute__((used)) static int cx25821_vidioc_s_std(struct file *file, void *priv,
				v4l2_std_id tvnorms)
{
	struct cx25821_channel *chan = video_drvdata(file);
	struct cx25821_dev *dev = chan->dev;

	if (dev->tvnorm == tvnorms)
		return 0;

	dev->tvnorm = tvnorms;
	chan->width = 720;
	chan->height = (dev->tvnorm & V4L2_STD_625_50) ? 576 : 480;

	medusa_set_videostandard(dev);

	return 0;
}