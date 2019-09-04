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
typedef  int u8 ;
struct solo_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TW286x_AUDIO_INPUT_GAIN_ADDR (int) ; 
 int /*<<< orphan*/  TW_AUDIO_INPUT_GAIN_ADDR (int) ; 
 int tw_readbyte (struct solo_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_writebyte (struct solo_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void tw28_set_audio_gain(struct solo_dev *solo_dev, u8 ch, u8 val)
{
	u8 old_val;
	u8 chip_num;

	/* Get the right chip and on-chip channel */
	chip_num = ch / 4;
	ch %= 4;

	old_val = tw_readbyte(solo_dev, chip_num,
			      TW286x_AUDIO_INPUT_GAIN_ADDR(ch),
			      TW_AUDIO_INPUT_GAIN_ADDR(ch));

	val = (old_val & ((ch % 2) ? 0x0f : 0xf0)) |
		((ch % 2) ? (val << 4) : val);

	tw_writebyte(solo_dev, chip_num, TW286x_AUDIO_INPUT_GAIN_ADDR(ch),
		     TW_AUDIO_INPUT_GAIN_ADDR(ch), val);
}