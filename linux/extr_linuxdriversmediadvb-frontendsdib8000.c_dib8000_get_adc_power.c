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
typedef  int u32 ;
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct dib8000_state {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int dib8000_read32 (struct dib8000_state*,int) ; 
 int* lut_1000ln_mant ; 

__attribute__((used)) static s32 dib8000_get_adc_power(struct dvb_frontend *fe, u8 mode)
{
	struct dib8000_state *state = fe->demodulator_priv;
	u32 ix = 0, tmp_val = 0, exp = 0, mant = 0;
	s32 val;

	val = dib8000_read32(state, 384);
	if (mode) {
		tmp_val = val;
		while (tmp_val >>= 1)
			exp++;
		mant = (val * 1000 / (1<<exp));
		ix = (u8)((mant-1000)/100); /* index of the LUT */
		val = (lut_1000ln_mant[ix] + 693*(exp-20) - 6908);
		val = (val*256)/1000;
	}
	return val;
}