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
struct stv0297_state {int dummy; } ;
struct dvb_frontend {struct stv0297_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  stv0297_readregs (struct stv0297_state*,int,int*,int) ; 

__attribute__((used)) static int stv0297_read_snr(struct dvb_frontend *fe, u16 * snr)
{
	struct stv0297_state *state = fe->demodulator_priv;
	u8 SNR[2];

	stv0297_readregs(state, 0x07, SNR, 2);
	*snr = SNR[1] << 8 | SNR[0];

	return 0;
}