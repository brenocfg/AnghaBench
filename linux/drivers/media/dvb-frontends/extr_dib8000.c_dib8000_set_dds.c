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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {TYPE_1__* pll; } ;
struct dib8000_state {int revision; TYPE_2__ cfg; } ;
typedef  scalar_t__ s32 ;
typedef  int s16 ;
struct TYPE_3__ {int ifreq; int internal; } ;

/* Variables and functions */
 int abs (scalar_t__) ; 
 int dib8000_read32 (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dib8000_write_word (struct dib8000_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,char,int) ; 

__attribute__((used)) static void dib8000_set_dds(struct dib8000_state *state, s32 offset_khz)
{
	s16 unit_khz_dds_val;
	u32 abs_offset_khz = abs(offset_khz);
	u32 dds = state->cfg.pll->ifreq & 0x1ffffff;
	u8 invert = !!(state->cfg.pll->ifreq & (1 << 25));
	u8 ratio;

	if (state->revision == 0x8090) {
		ratio = 4;
		unit_khz_dds_val = (1<<26) / (dib8000_read32(state, 23) / 1000);
		if (offset_khz < 0)
			dds = (1 << 26) - (abs_offset_khz * unit_khz_dds_val);
		else
			dds = (abs_offset_khz * unit_khz_dds_val);

		if (invert)
			dds = (1<<26) - dds;
	} else {
		ratio = 2;
		unit_khz_dds_val = (u16) (67108864 / state->cfg.pll->internal);

		if (offset_khz < 0)
			unit_khz_dds_val *= -1;

		/* IF tuner */
		if (invert)
			dds -= abs_offset_khz * unit_khz_dds_val;
		else
			dds += abs_offset_khz * unit_khz_dds_val;
	}

	dprintk("setting a DDS frequency offset of %c%dkHz\n", invert ? '-' : ' ', dds / unit_khz_dds_val);

	if (abs_offset_khz <= (state->cfg.pll->internal / ratio)) {
		/* Max dds offset is the half of the demod freq */
		dib8000_write_word(state, 26, invert);
		dib8000_write_word(state, 27, (u16)(dds >> 16) & 0x1ff);
		dib8000_write_word(state, 28, (u16)(dds & 0xffff));
	}
}