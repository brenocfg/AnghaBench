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
struct v4l2_frequency_band {scalar_t__ tuner; int index; int /*<<< orphan*/  capability; } ;
struct snd_tea575x {int /*<<< orphan*/  cannot_read_data; int /*<<< orphan*/  has_am; int /*<<< orphan*/  tea5759; } ;

/* Variables and functions */
 int BAND_AM ; 
 int BAND_FM ; 
 int BAND_FM_JAPAN ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_TUNER_CAP_HWSEEK_BOUNDED ; 
 struct v4l2_frequency_band* bands ; 

int snd_tea575x_enum_freq_bands(struct snd_tea575x *tea,
					struct v4l2_frequency_band *band)
{
	int index;

	if (band->tuner != 0)
		return -EINVAL;

	switch (band->index) {
	case 0:
		if (tea->tea5759)
			index = BAND_FM_JAPAN;
		else
			index = BAND_FM;
		break;
	case 1:
		if (tea->has_am) {
			index = BAND_AM;
			break;
		}
		/* Fall through */
	default:
		return -EINVAL;
	}

	*band = bands[index];
	if (!tea->cannot_read_data)
		band->capability |= V4L2_TUNER_CAP_HWSEEK_BOUNDED;

	return 0;
}