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
struct vivid_dev {int /*<<< orphan*/  sdr_fm_freq; int /*<<< orphan*/  sdr_adc_freq; } ;
struct v4l2_frequency {int tuner; int /*<<< orphan*/  type; int /*<<< orphan*/  frequency; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_TUNER_ADC ; 
 int /*<<< orphan*/  V4L2_TUNER_RF ; 
 struct vivid_dev* video_drvdata (struct file*) ; 

int vivid_sdr_g_frequency(struct file *file, void *fh,
		struct v4l2_frequency *vf)
{
	struct vivid_dev *dev = video_drvdata(file);

	switch (vf->tuner) {
	case 0:
		vf->frequency = dev->sdr_adc_freq;
		vf->type = V4L2_TUNER_ADC;
		return 0;
	case 1:
		vf->frequency = dev->sdr_fm_freq;
		vf->type = V4L2_TUNER_RF;
		return 0;
	default:
		return -EINVAL;
	}
}