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
struct vivid_dev {size_t input; int tv_freq; int /*<<< orphan*/  tpg; int /*<<< orphan*/ * std_signal_mode; int /*<<< orphan*/ * dv_timings_signal_mode; scalar_t__ loop_video; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPG_QUAL_COLOR ; 
 int /*<<< orphan*/  TPG_QUAL_GRAY ; 
 int /*<<< orphan*/  TPG_QUAL_NOISE ; 
 scalar_t__ VIVID_INVALID_SIGNAL (int /*<<< orphan*/ ) ; 
 int next_pseudo_random32 (int) ; 
 int /*<<< orphan*/  tpg_s_quality (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vivid_is_hdmi_cap (struct vivid_dev*) ; 
 scalar_t__ vivid_is_sdtv_cap (struct vivid_dev*) ; 
 scalar_t__ vivid_is_svid_cap (struct vivid_dev*) ; 
 int /*<<< orphan*/  vivid_is_tv_cap (struct vivid_dev*) ; 

void vivid_update_quality(struct vivid_dev *dev)
{
	unsigned freq_modulus;

	if (dev->loop_video && (vivid_is_svid_cap(dev) || vivid_is_hdmi_cap(dev))) {
		/*
		 * The 'noise' will only be replaced by the actual video
		 * if the output video matches the input video settings.
		 */
		tpg_s_quality(&dev->tpg, TPG_QUAL_NOISE, 0);
		return;
	}
	if (vivid_is_hdmi_cap(dev) &&
	    VIVID_INVALID_SIGNAL(dev->dv_timings_signal_mode[dev->input])) {
		tpg_s_quality(&dev->tpg, TPG_QUAL_NOISE, 0);
		return;
	}
	if (vivid_is_sdtv_cap(dev) &&
	    VIVID_INVALID_SIGNAL(dev->std_signal_mode[dev->input])) {
		tpg_s_quality(&dev->tpg, TPG_QUAL_NOISE, 0);
		return;
	}
	if (!vivid_is_tv_cap(dev)) {
		tpg_s_quality(&dev->tpg, TPG_QUAL_COLOR, 0);
		return;
	}

	/*
	 * There is a fake channel every 6 MHz at 49.25, 55.25, etc.
	 * From +/- 0.25 MHz around the channel there is color, and from
	 * +/- 1 MHz there is grayscale (chroma is lost).
	 * Everywhere else it is just noise.
	 */
	freq_modulus = (dev->tv_freq - 676 /* (43.25-1) * 16 */) % (6 * 16);
	if (freq_modulus > 2 * 16) {
		tpg_s_quality(&dev->tpg, TPG_QUAL_NOISE,
			next_pseudo_random32(dev->tv_freq ^ 0x55) & 0x3f);
		return;
	}
	if (freq_modulus < 12 /*0.75 * 16*/ || freq_modulus > 20 /*1.25 * 16*/)
		tpg_s_quality(&dev->tpg, TPG_QUAL_GRAY, 0);
	else
		tpg_s_quality(&dev->tpg, TPG_QUAL_COLOR, 0);
}