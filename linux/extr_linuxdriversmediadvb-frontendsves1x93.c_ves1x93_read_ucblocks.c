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
struct ves1x93_state {int dummy; } ;
struct dvb_frontend {struct ves1x93_state* demodulator_priv; } ;

/* Variables and functions */
 int ves1x93_readreg (struct ves1x93_state*,int) ; 
 int /*<<< orphan*/  ves1x93_writereg (struct ves1x93_state*,int,int) ; 

__attribute__((used)) static int ves1x93_read_ucblocks(struct dvb_frontend* fe, u32* ucblocks)
{
	struct ves1x93_state* state = fe->demodulator_priv;

	*ucblocks = ves1x93_readreg (state, 0x18) & 0x7f;

	if (*ucblocks == 0x7f)
		*ucblocks = 0xffffffff;   /* counter overflow... */

	ves1x93_writereg (state, 0x18, 0x00);  /* reset the counter */
	ves1x93_writereg (state, 0x18, 0x80);  /* dto. */

	return 0;
}