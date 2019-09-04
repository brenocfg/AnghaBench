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
typedef  scalar_t__ u8 ;
typedef  long u64 ;
typedef  scalar_t__ u32 ;
struct cx231xx {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ if_freq; scalar_t__ value; int /*<<< orphan*/  register_address; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DIF_MISC_CTRL ; 
 int /*<<< orphan*/  DIF_PLL_FREQ_WORD ; 
 TYPE_1__* Dif_set_array ; 
 scalar_t__ TUNER_MODE_FM_RADIO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  do_div (long,int) ; 
 int /*<<< orphan*/  vid_blk_read_word (struct cx231xx*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  vid_blk_write_word (struct cx231xx*,int /*<<< orphan*/ ,scalar_t__) ; 

void cx231xx_set_DIF_bandpass(struct cx231xx *dev, u32 if_freq,
		 u8 spectral_invert, u32 mode)
{
	unsigned long pll_freq_word;
	u32 dif_misc_ctrl_value = 0;
	u64 pll_freq_u64 = 0;
	u32 i = 0;

	dev_dbg(dev->dev, "if_freq=%d;spectral_invert=0x%x;mode=0x%x\n",
		if_freq, spectral_invert, mode);


	if (mode == TUNER_MODE_FM_RADIO) {
		pll_freq_word = 0x905A1CAC;
		vid_blk_write_word(dev, DIF_PLL_FREQ_WORD,  pll_freq_word);

	} else /*KSPROPERTY_TUNER_MODE_TV*/{
		/* Calculate the PLL frequency word based on the adjusted if_freq*/
		pll_freq_word = if_freq;
		pll_freq_u64 = (u64)pll_freq_word << 28L;
		do_div(pll_freq_u64, 50000000);
		pll_freq_word = (u32)pll_freq_u64;
		/*pll_freq_word = 0x3463497;*/
		vid_blk_write_word(dev, DIF_PLL_FREQ_WORD,  pll_freq_word);

		if (spectral_invert) {
			if_freq -= 400000;
			/* Enable Spectral Invert*/
			vid_blk_read_word(dev, DIF_MISC_CTRL,
					  &dif_misc_ctrl_value);
			dif_misc_ctrl_value = dif_misc_ctrl_value | 0x00200000;
			vid_blk_write_word(dev, DIF_MISC_CTRL,
					  dif_misc_ctrl_value);
		} else {
			if_freq += 400000;
			/* Disable Spectral Invert*/
			vid_blk_read_word(dev, DIF_MISC_CTRL,
					  &dif_misc_ctrl_value);
			dif_misc_ctrl_value = dif_misc_ctrl_value & 0xFFDFFFFF;
			vid_blk_write_word(dev, DIF_MISC_CTRL,
					  dif_misc_ctrl_value);
		}

		if_freq = (if_freq / 100000) * 100000;

		if (if_freq < 3000000)
			if_freq = 3000000;

		if (if_freq > 16000000)
			if_freq = 16000000;
	}

	dev_dbg(dev->dev, "Enter IF=%zu\n", ARRAY_SIZE(Dif_set_array));
	for (i = 0; i < ARRAY_SIZE(Dif_set_array); i++) {
		if (Dif_set_array[i].if_freq == if_freq) {
			vid_blk_write_word(dev,
			Dif_set_array[i].register_address, Dif_set_array[i].value);
		}
	}
}