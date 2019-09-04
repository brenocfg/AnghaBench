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
struct v4l2_frequency {int tuner; int /*<<< orphan*/  frequency; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct airspy {int /*<<< orphan*/  f_rf; int /*<<< orphan*/  dev; int /*<<< orphan*/  f_adc; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_TUNER_ADC ; 
 int /*<<< orphan*/  V4L2_TUNER_RF ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct airspy* video_drvdata (struct file*) ; 

__attribute__((used)) static int airspy_g_frequency(struct file *file, void *priv,
		struct v4l2_frequency *f)
{
	struct airspy *s = video_drvdata(file);
	int ret;

	if (f->tuner == 0) {
		f->type = V4L2_TUNER_ADC;
		f->frequency = s->f_adc;
		dev_dbg(s->dev, "ADC frequency=%u Hz\n", s->f_adc);
		ret = 0;
	} else if (f->tuner == 1) {
		f->type = V4L2_TUNER_RF;
		f->frequency = s->f_rf;
		dev_dbg(s->dev, "RF frequency=%u Hz\n", s->f_rf);
		ret = 0;
	} else {
		ret = -EINVAL;
	}

	return ret;
}