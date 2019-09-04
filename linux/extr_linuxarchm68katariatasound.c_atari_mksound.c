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
struct TYPE_2__ {int rd_data_reg_sel; unsigned char wd_data; } ;

/* Variables and functions */
 unsigned int HZ ; 
 unsigned int PSG_ENV_FREQ_10 ; 
 unsigned int PSG_FREQ ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_1__ sound_ym ; 

void atari_mksound (unsigned int hz, unsigned int ticks)
{
	/* Generates sound of some frequency for some number of clock
	   ticks.  */
	unsigned long flags;
	unsigned char tmp;
	int period;

	local_irq_save(flags);


	/* Disable generator A in mixer control.  */
	sound_ym.rd_data_reg_sel = 7;
	tmp = sound_ym.rd_data_reg_sel;
	tmp |= 011;
	sound_ym.wd_data = tmp;

	if (hz) {
	    /* Convert from frequency value to PSG period value (base
	       frequency 125 kHz).  */

	    period = PSG_FREQ / hz;

	    if (period > 0xfff) period = 0xfff;

	/* Set generator A frequency to hz.  */
	sound_ym.rd_data_reg_sel = 0;
	sound_ym.wd_data = period & 0xff;
	sound_ym.rd_data_reg_sel = 1;
	sound_ym.wd_data = (period >> 8) & 0xf;
	if (ticks) {
		/* Set length of envelope (max 8 sec).  */
		int length = (ticks * PSG_ENV_FREQ_10) / HZ / 10;

		if (length > 0xffff) length = 0xffff;
		sound_ym.rd_data_reg_sel = 11;
		sound_ym.wd_data = length & 0xff;
		sound_ym.rd_data_reg_sel = 12;
		sound_ym.wd_data = length >> 8;
		/* Envelope form: max -> min single.  */
		sound_ym.rd_data_reg_sel = 13;
		sound_ym.wd_data = 0;
		/* Use envelope for generator A.  */
		sound_ym.rd_data_reg_sel = 8;
		sound_ym.wd_data = 0x10;
	} else {
		/* Set generator A level to maximum, no envelope.  */
		sound_ym.rd_data_reg_sel = 8;
		sound_ym.wd_data = 15;
	}
	/* Turn on generator A in mixer control.  */
	sound_ym.rd_data_reg_sel = 7;
	tmp &= ~1;
	sound_ym.wd_data = tmp;
	}
	local_irq_restore(flags);
}