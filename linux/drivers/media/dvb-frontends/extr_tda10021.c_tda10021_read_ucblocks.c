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
struct tda10021_state {int dummy; } ;
struct dvb_frontend {struct tda10021_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  _tda10021_writereg (struct tda10021_state*,int,int) ; 
 int* tda10021_inittab ; 
 int tda10021_readreg (struct tda10021_state*,int) ; 

__attribute__((used)) static int tda10021_read_ucblocks(struct dvb_frontend* fe, u32* ucblocks)
{
	struct tda10021_state* state = fe->demodulator_priv;

	*ucblocks = tda10021_readreg (state, 0x13) & 0x7f;
	if (*ucblocks == 0x7f)
		*ucblocks = 0xffffffff;

	/* reset uncorrected block counter */
	_tda10021_writereg (state, 0x10, tda10021_inittab[0x10] & 0xdf);
	_tda10021_writereg (state, 0x10, tda10021_inittab[0x10]);

	return 0;
}