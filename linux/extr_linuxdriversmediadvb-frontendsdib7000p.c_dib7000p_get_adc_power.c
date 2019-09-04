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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct dvb_frontend {struct dib7000p_state* demodulator_priv; } ;
struct dib7000p_state {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int dib7000p_read_word (struct dib7000p_state*,int) ; 
 int /*<<< orphan*/  dprintk (char*,int,...) ; 
 int* lut_1000ln_mant ; 

__attribute__((used)) static s32 dib7000p_get_adc_power(struct dvb_frontend *fe)
{
	struct dib7000p_state *state = fe->demodulator_priv;
	u32 tmp_val = 0, exp = 0, mant = 0;
	s32 pow_i;
	u16 buf[2];
	u8 ix = 0;

	buf[0] = dib7000p_read_word(state, 0x184);
	buf[1] = dib7000p_read_word(state, 0x185);
	pow_i = (buf[0] << 16) | buf[1];
	dprintk("raw pow_i = %d\n", pow_i);

	tmp_val = pow_i;
	while (tmp_val >>= 1)
		exp++;

	mant = (pow_i * 1000 / (1 << exp));
	dprintk(" mant = %d exp = %d\n", mant / 1000, exp);

	ix = (u8) ((mant - 1000) / 100);	/* index of the LUT */
	dprintk(" ix = %d\n", ix);

	pow_i = (lut_1000ln_mant[ix] + 693 * (exp - 20) - 6908);
	pow_i = (pow_i << 8) / 1000;
	dprintk(" pow_i = %d\n", pow_i);

	return pow_i;
}