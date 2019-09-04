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
struct v4l2_frequency_band {int tuner; size_t index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct v4l2_frequency_band*) ; 
 int EINVAL ; 
 struct v4l2_frequency_band* bands ; 
 struct v4l2_frequency_band* bands_rf ; 

__attribute__((used)) static int airspy_enum_freq_bands(struct file *file, void *priv,
		struct v4l2_frequency_band *band)
{
	int ret;

	if (band->tuner == 0) {
		if (band->index >= ARRAY_SIZE(bands)) {
			ret = -EINVAL;
		} else {
			*band = bands[band->index];
			ret = 0;
		}
	} else if (band->tuner == 1) {
		if (band->index >= ARRAY_SIZE(bands_rf)) {
			ret = -EINVAL;
		} else {
			*band = bands_rf[band->index];
			ret = 0;
		}
	} else {
		ret = -EINVAL;
	}

	return ret;
}