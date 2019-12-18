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
struct lgdt3306a_state {int dummy; } ;
struct dvb_frontend {struct lgdt3306a_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_info (char*,int) ; 
 int read_reg (struct lgdt3306a_state*,int) ; 

__attribute__((used)) static int lgdt3306a_read_ber(struct dvb_frontend *fe, u32 *ber)
{
	struct lgdt3306a_state *state = fe->demodulator_priv;
	u32 tmp;

	*ber = 0;
#if 1
	/* FGR - FIXME - I don't know what value is expected by dvb_core
	 * what is the scale of the value?? */
	tmp =              read_reg(state, 0x00fc); /* NBERVALUE[24-31] */
	tmp = (tmp << 8) | read_reg(state, 0x00fd); /* NBERVALUE[16-23] */
	tmp = (tmp << 8) | read_reg(state, 0x00fe); /* NBERVALUE[8-15] */
	tmp = (tmp << 8) | read_reg(state, 0x00ff); /* NBERVALUE[0-7] */
	*ber = tmp;
	dbg_info("ber=%u\n", tmp);
#endif
	return 0;
}