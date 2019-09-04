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
struct stv0297_state {int dummy; } ;
struct dvb_frontend {struct stv0297_state* demodulator_priv; } ;

/* Variables and functions */
 int stv0297_readreg (struct stv0297_state*,int) ; 
 int /*<<< orphan*/  stv0297_writereg_mask (struct stv0297_state*,int,int,int) ; 

__attribute__((used)) static int stv0297_read_ucblocks(struct dvb_frontend *fe, u32 * ucblocks)
{
	struct stv0297_state *state = fe->demodulator_priv;

	stv0297_writereg_mask(state, 0xDF, 0x03, 0x03); /* freeze the counters */

	*ucblocks = (stv0297_readreg(state, 0xD5) << 8)
		| stv0297_readreg(state, 0xD4);

	stv0297_writereg_mask(state, 0xDF, 0x03, 0x02); /* clear the counters */
	stv0297_writereg_mask(state, 0xDF, 0x03, 0x01); /* re-enable the counters */

	return 0;
}