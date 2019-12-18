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
struct ves1820_state {int dummy; } ;
struct dvb_frontend {struct ves1820_state* demodulator_priv; } ;

/* Variables and functions */
 int* ves1820_inittab ; 
 int ves1820_readreg (struct ves1820_state*,int) ; 
 int /*<<< orphan*/  ves1820_writereg (struct ves1820_state*,int,int) ; 

__attribute__((used)) static int ves1820_read_ucblocks(struct dvb_frontend* fe, u32* ucblocks)
{
	struct ves1820_state* state = fe->demodulator_priv;

	*ucblocks = ves1820_readreg(state, 0x13) & 0x7f;
	if (*ucblocks == 0x7f)
		*ucblocks = 0xffffffff;

	/* reset uncorrected block counter */
	ves1820_writereg(state, 0x10, ves1820_inittab[0x10] & 0xdf);
	ves1820_writereg(state, 0x10, ves1820_inittab[0x10]);

	return 0;
}