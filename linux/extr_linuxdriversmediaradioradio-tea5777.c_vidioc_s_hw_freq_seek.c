#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct v4l2_hw_freq_seek {scalar_t__ rangelow; scalar_t__ rangehigh; scalar_t__ seek_upward; scalar_t__ wrap_around; scalar_t__ tuner; } ;
struct radio_tea5777 {int band; scalar_t__ freq; scalar_t__ seek_rangelow; scalar_t__ seek_rangehigh; int read_reg; int /*<<< orphan*/  write_reg; int /*<<< orphan*/  has_am; } ;
struct file {int f_flags; } ;
struct TYPE_3__ {scalar_t__ rangelow; scalar_t__ rangehigh; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int BAND_AM ; 
 int EINVAL ; 
 int ENODATA ; 
 int EWOULDBLOCK ; 
 int O_NONBLOCK ; 
 int TEA5777_R_BLIM_MASK ; 
 int TEA5777_R_FM_PLL_MASK ; 
 int TEA5777_R_SFOUND_MASK ; 
 int /*<<< orphan*/  TEA5777_W_PROGBLIM_MASK ; 
 int /*<<< orphan*/  TEA5777_W_SEARCH_MASK ; 
 int /*<<< orphan*/  TEA5777_W_UPDWN_MASK ; 
 TYPE_1__* bands ; 
 scalar_t__ clamp (scalar_t__,scalar_t__,scalar_t__) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int radio_tea5777_set_freq (struct radio_tea5777*) ; 
 int radio_tea5777_update_read_reg (struct radio_tea5777*,int) ; 
 int tea5777_freq_to_v4l2_freq (struct radio_tea5777*,int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 struct radio_tea5777* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_hw_freq_seek(struct file *file, void *fh,
					const struct v4l2_hw_freq_seek *a)
{
	struct radio_tea5777 *tea = video_drvdata(file);
	unsigned long timeout;
	u32 rangelow = a->rangelow;
	u32 rangehigh = a->rangehigh;
	int i, res, spacing;
	u32 orig_freq;

	if (a->tuner || a->wrap_around)
		return -EINVAL;

	if (file->f_flags & O_NONBLOCK)
		return -EWOULDBLOCK;

	if (rangelow || rangehigh) {
		for (i = 0; i < ARRAY_SIZE(bands); i++) {
			if (i == BAND_AM && !tea->has_am)
				continue;
			if (bands[i].rangelow  >= rangelow &&
			    bands[i].rangehigh <= rangehigh)
				break;
		}
		if (i == ARRAY_SIZE(bands))
			return -EINVAL; /* No matching band found */

		tea->band = i;
		if (tea->freq < rangelow || tea->freq > rangehigh) {
			tea->freq = clamp(tea->freq, rangelow,
						     rangehigh);
			res = radio_tea5777_set_freq(tea);
			if (res)
				return res;
		}
	} else {
		rangelow  = bands[tea->band].rangelow;
		rangehigh = bands[tea->band].rangehigh;
	}

	spacing   = (tea->band == BAND_AM) ? (5 * 16) : (200 * 16); /* kHz */
	orig_freq = tea->freq;

	tea->write_reg |= TEA5777_W_PROGBLIM_MASK;
	if (tea->seek_rangelow != rangelow) {
		tea->write_reg &= ~TEA5777_W_UPDWN_MASK;
		tea->freq = rangelow;
		res = radio_tea5777_set_freq(tea);
		if (res)
			goto leave;
		tea->seek_rangelow = rangelow;
	}
	if (tea->seek_rangehigh != rangehigh) {
		tea->write_reg |= TEA5777_W_UPDWN_MASK;
		tea->freq = rangehigh;
		res = radio_tea5777_set_freq(tea);
		if (res)
			goto leave;
		tea->seek_rangehigh = rangehigh;
	}
	tea->write_reg &= ~TEA5777_W_PROGBLIM_MASK;

	tea->write_reg |= TEA5777_W_SEARCH_MASK;
	if (a->seek_upward) {
		tea->write_reg |= TEA5777_W_UPDWN_MASK;
		tea->freq = orig_freq + spacing;
	} else {
		tea->write_reg &= ~TEA5777_W_UPDWN_MASK;
		tea->freq = orig_freq - spacing;
	}
	res = radio_tea5777_set_freq(tea);
	if (res)
		goto leave;

	timeout = jiffies + msecs_to_jiffies(5000);
	for (;;) {
		if (time_after(jiffies, timeout)) {
			res = -ENODATA;
			break;
		}

		res = radio_tea5777_update_read_reg(tea, 100);
		if (res)
			break;

		/*
		 * Note we use tea->freq to track how far we've searched sofar
		 * this is necessary to ensure we continue seeking at the right
		 * point, in the write_before_read case.
		 */
		tea->freq = (tea->read_reg & TEA5777_R_FM_PLL_MASK);
		tea->freq = tea5777_freq_to_v4l2_freq(tea, tea->freq);

		if ((tea->read_reg & TEA5777_R_SFOUND_MASK)) {
			tea->write_reg &= ~TEA5777_W_SEARCH_MASK;
			return 0;
		}

		if (tea->read_reg & TEA5777_R_BLIM_MASK) {
			res = -ENODATA;
			break;
		}

		/* Force read_reg update */
		tea->read_reg = -1;
	}
leave:
	tea->write_reg &= ~TEA5777_W_PROGBLIM_MASK;
	tea->write_reg &= ~TEA5777_W_SEARCH_MASK;
	tea->freq = orig_freq;
	radio_tea5777_set_freq(tea);
	return res;
}