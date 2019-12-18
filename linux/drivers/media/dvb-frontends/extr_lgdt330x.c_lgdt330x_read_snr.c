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
struct lgdt330x_state {int snr; } ;
struct dvb_frontend {struct lgdt330x_state* demodulator_priv; } ;

/* Variables and functions */

__attribute__((used)) static int lgdt330x_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct lgdt330x_state *state = fe->demodulator_priv;

	*snr = (state->snr) >> 16; /* Convert from 8.24 fixed-point to 8.8 */

	return 0;
}