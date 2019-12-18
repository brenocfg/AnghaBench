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
struct v4l2_frequency_band {scalar_t__ tuner; size_t index; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t TOT_BANDS ; 
 struct v4l2_frequency_band* vivid_radio_bands ; 

int vivid_radio_rx_enum_freq_bands(struct file *file, void *fh, struct v4l2_frequency_band *band)
{
	if (band->tuner != 0)
		return -EINVAL;

	if (band->index >= TOT_BANDS)
		return -EINVAL;

	*band = vivid_radio_bands[band->index];
	return 0;
}