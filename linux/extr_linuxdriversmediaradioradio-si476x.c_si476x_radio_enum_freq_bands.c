#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_frequency_band {scalar_t__ tuner; size_t index; } ;
struct si476x_radio {TYPE_1__* core; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int chip_id; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct v4l2_frequency_band*) ; 
 int EINVAL ; 
 size_t SI476X_BAND_FM ; 
#define  SI476X_CHIP_SI4761 130 
#define  SI476X_CHIP_SI4764 129 
#define  SI476X_CHIP_SI4768 128 
 struct v4l2_frequency_band* si476x_bands ; 
 struct si476x_radio* video_drvdata (struct file*) ; 

__attribute__((used)) static int si476x_radio_enum_freq_bands(struct file *file, void *priv,
					struct v4l2_frequency_band *band)
{
	int err;
	struct si476x_radio *radio = video_drvdata(file);

	if (band->tuner != 0)
		return -EINVAL;

	switch (radio->core->chip_id) {
		/* AM/FM tuners -- all bands are supported */
	case SI476X_CHIP_SI4761:
	case SI476X_CHIP_SI4764:
		if (band->index < ARRAY_SIZE(si476x_bands)) {
			*band = si476x_bands[band->index];
			err = 0;
		} else {
			err = -EINVAL;
		}
		break;
		/* FM companion tuner chips -- only FM bands are
		 * supported */
	case SI476X_CHIP_SI4768:
		if (band->index == SI476X_BAND_FM) {
			*band = si476x_bands[band->index];
			err = 0;
		} else {
			err = -EINVAL;
		}
		break;
	default:
		err = -EINVAL;
	}

	return err;
}