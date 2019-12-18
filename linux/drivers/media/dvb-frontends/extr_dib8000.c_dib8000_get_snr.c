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
typedef  int u32 ;
typedef  int u16 ;
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct dib8000_state {int revision; } ;

/* Variables and functions */
 int dib8000_read_word (struct dib8000_state*,int) ; 

__attribute__((used)) static u32 dib8000_get_snr(struct dvb_frontend *fe)
{
	struct dib8000_state *state = fe->demodulator_priv;
	u32 n, s, exp;
	u16 val;

	if (state->revision != 0x8090)
		val = dib8000_read_word(state, 542);
	else
		val = dib8000_read_word(state, 544);
	n = (val >> 6) & 0xff;
	exp = (val & 0x3f);
	if ((exp & 0x20) != 0)
		exp -= 0x40;
	n <<= exp+16;

	if (state->revision != 0x8090)
		val = dib8000_read_word(state, 543);
	else
		val = dib8000_read_word(state, 545);
	s = (val >> 6) & 0xff;
	exp = (val & 0x3f);
	if ((exp & 0x20) != 0)
		exp -= 0x40;
	s <<= exp+16;

	if (n > 0) {
		u32 t = (s/n) << 16;
		return t + ((s << 16) - n*t) / n;
	}
	return 0xffffffff;
}