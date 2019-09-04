#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_hw_freq_seek {scalar_t__ rangelow; scalar_t__ rangehigh; scalar_t__ seek_upward; scalar_t__ wrap_around; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct si470x_device {int band; int* registers; int (* set_register ) (struct si470x_device*,size_t) ;TYPE_1__ videodev; int /*<<< orphan*/  completion; } ;
struct TYPE_5__ {scalar_t__ rangelow; scalar_t__ rangehigh; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
 int ENODATA ; 
 size_t POWERCFG ; 
 int POWERCFG_SEEK ; 
 int POWERCFG_SEEKUP ; 
 int POWERCFG_SKMODE ; 
 size_t STATUSRSSI ; 
 int STATUSRSSI_SF ; 
 int STATUSRSSI_STC ; 
 TYPE_2__* bands ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seek_timeout ; 
 int si470x_get_freq (struct si470x_device*,unsigned int*) ; 
 int si470x_set_band (struct si470x_device*,int) ; 
 int si470x_set_freq (struct si470x_device*,unsigned int) ; 
 int stub1 (struct si470x_device*,size_t) ; 
 int stub2 (struct si470x_device*,size_t) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si470x_set_seek(struct si470x_device *radio,
			   const struct v4l2_hw_freq_seek *seek)
{
	int band, retval;
	unsigned int freq;
	bool timed_out = false;
	unsigned long time_left;

	/* set band */
	if (seek->rangelow || seek->rangehigh) {
		for (band = 0; band < ARRAY_SIZE(bands); band++) {
			if (bands[band].rangelow  == seek->rangelow &&
			    bands[band].rangehigh == seek->rangehigh)
				break;
		}
		if (band == ARRAY_SIZE(bands))
			return -EINVAL; /* No matching band found */
	} else
		band = 1; /* If nothing is specified seek 76 - 108 Mhz */

	if (radio->band != band) {
		retval = si470x_get_freq(radio, &freq);
		if (retval)
			return retval;
		retval = si470x_set_band(radio, band);
		if (retval)
			return retval;
		retval = si470x_set_freq(radio, freq);
		if (retval)
			return retval;
	}

	/* start seeking */
	radio->registers[POWERCFG] |= POWERCFG_SEEK;
	if (seek->wrap_around)
		radio->registers[POWERCFG] &= ~POWERCFG_SKMODE;
	else
		radio->registers[POWERCFG] |= POWERCFG_SKMODE;
	if (seek->seek_upward)
		radio->registers[POWERCFG] |= POWERCFG_SEEKUP;
	else
		radio->registers[POWERCFG] &= ~POWERCFG_SEEKUP;
	retval = radio->set_register(radio, POWERCFG);
	if (retval < 0)
		return retval;

	/* wait till tune operation has completed */
	reinit_completion(&radio->completion);
	time_left = wait_for_completion_timeout(&radio->completion,
						msecs_to_jiffies(seek_timeout));
	if (time_left == 0)
		timed_out = true;

	if ((radio->registers[STATUSRSSI] & STATUSRSSI_STC) == 0)
		dev_warn(&radio->videodev.dev, "seek does not complete\n");
	if (radio->registers[STATUSRSSI] & STATUSRSSI_SF)
		dev_warn(&radio->videodev.dev,
			"seek failed / band limit reached\n");

	/* stop seeking */
	radio->registers[POWERCFG] &= ~POWERCFG_SEEK;
	retval = radio->set_register(radio, POWERCFG);

	/* try again, if timed out */
	if (retval == 0 && timed_out)
		return -ENODATA;
	return retval;
}