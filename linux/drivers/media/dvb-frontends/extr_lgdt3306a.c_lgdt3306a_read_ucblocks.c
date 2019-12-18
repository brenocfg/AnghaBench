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
typedef  int /*<<< orphan*/  u32 ;
struct lgdt3306a_state {int dummy; } ;
struct dvb_frontend {struct lgdt3306a_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_reg (struct lgdt3306a_state*,int) ; 

__attribute__((used)) static int lgdt3306a_read_ucblocks(struct dvb_frontend *fe, u32 *ucblocks)
{
	struct lgdt3306a_state *state = fe->demodulator_priv;

	*ucblocks = 0;
#if 1
	/* FGR - FIXME - I don't know what value is expected by dvb_core
	 * what happens when value wraps? */
	*ucblocks = read_reg(state, 0x00f4); /* TPIFTPERRCNT[0-7] */
	dbg_info("ucblocks=%u\n", *ucblocks);
#endif

	return 0;
}