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
struct vivid_dev {int radio_tx_subchans; } ;
struct v4l2_modulator {int txsubchans; scalar_t__ index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vivid_dev* video_drvdata (struct file*) ; 

int vidioc_s_modulator(struct file *file, void *fh, const struct v4l2_modulator *a)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (a->index)
		return -EINVAL;
	if (a->txsubchans & ~0x13)
		return -EINVAL;
	dev->radio_tx_subchans = a->txsubchans;
	return 0;
}