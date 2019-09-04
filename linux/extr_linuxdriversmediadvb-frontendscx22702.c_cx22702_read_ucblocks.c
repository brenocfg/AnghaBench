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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct dvb_frontend {struct cx22702_state* demodulator_priv; } ;
struct cx22702_state {scalar_t__ prevUCBlocks; } ;

/* Variables and functions */
 scalar_t__ cx22702_readreg (struct cx22702_state*,int) ; 

__attribute__((used)) static int cx22702_read_ucblocks(struct dvb_frontend *fe, u32 *ucblocks)
{
	struct cx22702_state *state = fe->demodulator_priv;

	u8 _ucblocks;

	/* RS Uncorrectable Packet Count then reset */
	_ucblocks = cx22702_readreg(state, 0xE3);
	if (state->prevUCBlocks < _ucblocks)
		*ucblocks = (_ucblocks - state->prevUCBlocks);
	else
		*ucblocks = state->prevUCBlocks - _ucblocks;
	state->prevUCBlocks = _ucblocks;

	return 0;
}