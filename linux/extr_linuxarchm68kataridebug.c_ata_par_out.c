#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rd_data_reg_sel; char wd_data; } ;
struct TYPE_3__ {int par_dt_reg; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  MFPDELAY () ; 
 int loops_per_jiffy ; 
 TYPE_2__ sound_ym ; 
 TYPE_1__ st_mfp ; 

__attribute__((used)) static int ata_par_out(char c)
{
	unsigned char tmp;
	/* This a some-seconds timeout in case no printer is connected */
	unsigned long i = loops_per_jiffy > 1 ? loops_per_jiffy : 10000000/HZ;

	while ((st_mfp.par_dt_reg & 1) && --i) /* wait for BUSY == L */
		;
	if (!i)
		return 0;

	sound_ym.rd_data_reg_sel = 15;	/* select port B */
	sound_ym.wd_data = c;		/* put char onto port */
	sound_ym.rd_data_reg_sel = 14;	/* select port A */
	tmp = sound_ym.rd_data_reg_sel;
	sound_ym.wd_data = tmp & ~0x20;	/* set strobe L */
	MFPDELAY();			/* wait a bit */
	sound_ym.wd_data = tmp | 0x20;	/* set strobe H */
	return 1;
}