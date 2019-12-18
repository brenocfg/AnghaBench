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
typedef  int u16 ;
struct lg216x_state {int dummy; } ;
struct dvb_frontend {struct lg216x_state* demodulator_priv; } ;

/* Variables and functions */
 int lg216x_read_reg (struct lg216x_state*,int,int*) ; 
 scalar_t__ lg_fail (int) ; 

__attribute__((used)) static int lg2161_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct lg216x_state *state = fe->demodulator_priv;
	u8 snr1, snr2;
	int ret;

	*snr = 0;

	ret = lg216x_read_reg(state, 0x0302, &snr1);
	if (lg_fail(ret))
		goto fail;

	ret = lg216x_read_reg(state, 0x0303, &snr2);
	if (lg_fail(ret))
		goto fail;

	if ((snr1 == 0xba) || (snr2 == 0xfd))
		*snr = 0;
	else

	*snr =  ((snr1 >> 4) * 100) + ((snr1 & 0x0f) * 10) + (snr2 & 0x0f);
fail:
	return ret;
}