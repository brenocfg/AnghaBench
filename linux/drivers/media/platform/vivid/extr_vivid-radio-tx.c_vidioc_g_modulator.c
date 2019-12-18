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
struct vivid_dev {int /*<<< orphan*/  radio_tx_subchans; scalar_t__ radio_tx_rds_controls; } ;
struct v4l2_modulator {scalar_t__ index; int capability; int /*<<< orphan*/  txsubchans; int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AM_FREQ_RANGE_LOW ; 
 int EINVAL ; 
 int /*<<< orphan*/  FM_FREQ_RANGE_HIGH ; 
 int V4L2_TUNER_CAP_FREQ_BANDS ; 
 int V4L2_TUNER_CAP_LOW ; 
 int V4L2_TUNER_CAP_RDS ; 
 int V4L2_TUNER_CAP_RDS_BLOCK_IO ; 
 int V4L2_TUNER_CAP_RDS_CONTROLS ; 
 int V4L2_TUNER_CAP_STEREO ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 

int vidioc_g_modulator(struct file *file, void *fh, struct v4l2_modulator *a)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (a->index > 0)
		return -EINVAL;

	strscpy(a->name, "AM/FM/SW Transmitter", sizeof(a->name));
	a->capability = V4L2_TUNER_CAP_LOW | V4L2_TUNER_CAP_STEREO |
			V4L2_TUNER_CAP_FREQ_BANDS | V4L2_TUNER_CAP_RDS |
			(dev->radio_tx_rds_controls ?
				V4L2_TUNER_CAP_RDS_CONTROLS :
				V4L2_TUNER_CAP_RDS_BLOCK_IO);
	a->rangelow = AM_FREQ_RANGE_LOW;
	a->rangehigh = FM_FREQ_RANGE_HIGH;
	a->txsubchans = dev->radio_tx_subchans;
	return 0;
}