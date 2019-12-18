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
typedef  int u16 ;
struct lgdt3306a_state {int snr; } ;
struct dvb_frontend {struct lgdt3306a_state* demodulator_priv; } ;

/* Variables and functions */
 int lgdt3306a_calculate_snr_x100 (struct lgdt3306a_state*) ; 

__attribute__((used)) static int lgdt3306a_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct lgdt3306a_state *state = fe->demodulator_priv;

	state->snr = lgdt3306a_calculate_snr_x100(state);
	/* report SNR in dB * 10 */
	*snr = state->snr/10;

	return 0;
}