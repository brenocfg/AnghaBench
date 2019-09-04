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
struct vivid_dev {scalar_t__ radio_rx_hw_seek_mode; int radio_rx_freq; int /*<<< orphan*/  radio_rx_hw_seek_prog_lim; } ;
struct v4l2_hw_freq_seek {int rangelow; unsigned int rangehigh; scalar_t__ wrap_around; scalar_t__ seek_upward; scalar_t__ tuner; } ;
struct file {int f_flags; } ;
struct TYPE_2__ {int rangelow; unsigned int rangehigh; } ;

/* Variables and functions */
 unsigned int BAND_AM ; 
 int EINVAL ; 
 int ENODATA ; 
 int EWOULDBLOCK ; 
 int O_NONBLOCK ; 
 unsigned int TOT_BANDS ; 
 scalar_t__ VIVID_HW_SEEK_BOUNDED ; 
 scalar_t__ VIVID_HW_SEEK_WRAP ; 
 unsigned int clamp (unsigned int,unsigned int,unsigned int) ; 
 struct vivid_dev* video_drvdata (struct file*) ; 
 TYPE_1__* vivid_radio_bands ; 

int vivid_radio_rx_s_hw_freq_seek(struct file *file, void *fh, const struct v4l2_hw_freq_seek *a)
{
	struct vivid_dev *dev = video_drvdata(file);
	unsigned low, high;
	unsigned freq;
	unsigned spacing;
	unsigned band;

	if (a->tuner)
		return -EINVAL;
	if (a->wrap_around && dev->radio_rx_hw_seek_mode == VIVID_HW_SEEK_BOUNDED)
		return -EINVAL;

	if (!a->wrap_around && dev->radio_rx_hw_seek_mode == VIVID_HW_SEEK_WRAP)
		return -EINVAL;
	if (!a->rangelow ^ !a->rangehigh)
		return -EINVAL;

	if (file->f_flags & O_NONBLOCK)
		return -EWOULDBLOCK;

	if (a->rangelow) {
		for (band = 0; band < TOT_BANDS; band++)
			if (a->rangelow >= vivid_radio_bands[band].rangelow &&
			    a->rangehigh <= vivid_radio_bands[band].rangehigh)
				break;
		if (band == TOT_BANDS)
			return -EINVAL;
		if (!dev->radio_rx_hw_seek_prog_lim &&
		    (a->rangelow != vivid_radio_bands[band].rangelow ||
		     a->rangehigh != vivid_radio_bands[band].rangehigh))
			return -EINVAL;
		low = a->rangelow;
		high = a->rangehigh;
	} else {
		for (band = 0; band < TOT_BANDS; band++)
			if (dev->radio_rx_freq >= vivid_radio_bands[band].rangelow &&
			    dev->radio_rx_freq <= vivid_radio_bands[band].rangehigh)
				break;
		if (band == TOT_BANDS)
			return -EINVAL;
		low = vivid_radio_bands[band].rangelow;
		high = vivid_radio_bands[band].rangehigh;
	}
	spacing = band == BAND_AM ? 1600 : 16000;
	freq = clamp(dev->radio_rx_freq, low, high);

	if (a->seek_upward) {
		freq = spacing * (freq / spacing) + spacing;
		if (freq > high) {
			if (!a->wrap_around)
				return -ENODATA;
			freq = spacing * (low / spacing) + spacing;
			if (freq >= dev->radio_rx_freq)
				return -ENODATA;
		}
	} else {
		freq = spacing * ((freq + spacing - 1) / spacing) - spacing;
		if (freq < low) {
			if (!a->wrap_around)
				return -ENODATA;
			freq = spacing * ((high + spacing - 1) / spacing) - spacing;
			if (freq <= dev->radio_rx_freq)
				return -ENODATA;
		}
	}
	return 0;
}