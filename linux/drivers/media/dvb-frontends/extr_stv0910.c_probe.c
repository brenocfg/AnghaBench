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
struct stv {int tsgeneral; int tscfgh; int tsspeed; int i2crpt; scalar_t__ single; scalar_t__ started; int /*<<< orphan*/  receive_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  RCVMODE_NONE ; 
 int /*<<< orphan*/  RSTV0910_CFGEXT ; 
 int /*<<< orphan*/  RSTV0910_GENCFG ; 
 int /*<<< orphan*/  RSTV0910_I2CCFG ; 
 int /*<<< orphan*/  RSTV0910_MID ; 
 int /*<<< orphan*/  RSTV0910_OUTCFG ; 
 int /*<<< orphan*/  RSTV0910_P1_CAR3CFG ; 
 int /*<<< orphan*/  RSTV0910_P1_DMDCFG4 ; 
 int /*<<< orphan*/  RSTV0910_P1_I2CRPT ; 
 int /*<<< orphan*/  RSTV0910_P1_TMGCFG2 ; 
 int /*<<< orphan*/  RSTV0910_P1_TNRCFG2 ; 
 int /*<<< orphan*/  RSTV0910_P1_TSCFGH ; 
 int /*<<< orphan*/  RSTV0910_P1_TSCFGL ; 
 int /*<<< orphan*/  RSTV0910_P1_TSCFGM ; 
 int /*<<< orphan*/  RSTV0910_P1_TSINSDELL ; 
 int /*<<< orphan*/  RSTV0910_P1_TSINSDELM ; 
 int /*<<< orphan*/  RSTV0910_P1_TSPIDFLT1 ; 
 int /*<<< orphan*/  RSTV0910_P1_TSSPEED ; 
 int /*<<< orphan*/  RSTV0910_P2_CAR3CFG ; 
 int /*<<< orphan*/  RSTV0910_P2_DMDCFG4 ; 
 int /*<<< orphan*/  RSTV0910_P2_I2CRPT ; 
 int /*<<< orphan*/  RSTV0910_P2_TMGCFG2 ; 
 int /*<<< orphan*/  RSTV0910_P2_TNRCFG2 ; 
 int /*<<< orphan*/  RSTV0910_P2_TSCFGH ; 
 int /*<<< orphan*/  RSTV0910_P2_TSCFGL ; 
 int /*<<< orphan*/  RSTV0910_P2_TSCFGM ; 
 int /*<<< orphan*/  RSTV0910_P2_TSINSDELL ; 
 int /*<<< orphan*/  RSTV0910_P2_TSINSDELM ; 
 int /*<<< orphan*/  RSTV0910_P2_TSPIDFLT1 ; 
 int /*<<< orphan*/  RSTV0910_P2_TSSPEED ; 
 int /*<<< orphan*/  RSTV0910_PADCFG ; 
 int /*<<< orphan*/  RSTV0910_SYNTCTRL ; 
 int /*<<< orphan*/  RSTV0910_TSGENERAL ; 
 int /*<<< orphan*/  RSTV0910_TSTRES0 ; 
 int /*<<< orphan*/  init_diseqc (struct stv*) ; 
 scalar_t__ read_reg (struct stv*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  set_mclock (struct stv*,int) ; 
 int /*<<< orphan*/  write_reg (struct stv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int probe(struct stv *state)
{
	u8 id;

	state->receive_mode = RCVMODE_NONE;
	state->started = 0;

	if (read_reg(state, RSTV0910_MID, &id) < 0)
		return -ENODEV;

	if (id != 0x51)
		return -EINVAL;

	/* Configure the I2C repeater to off */
	write_reg(state, RSTV0910_P1_I2CRPT, 0x24);
	/* Configure the I2C repeater to off */
	write_reg(state, RSTV0910_P2_I2CRPT, 0x24);
	/* Set the I2C to oversampling ratio */
	write_reg(state, RSTV0910_I2CCFG, 0x88); /* state->i2ccfg */

	write_reg(state, RSTV0910_OUTCFG,    0x00); /* OUTCFG */
	write_reg(state, RSTV0910_PADCFG,    0x05); /* RFAGC Pads Dev = 05 */
	write_reg(state, RSTV0910_SYNTCTRL,  0x02); /* SYNTCTRL */
	write_reg(state, RSTV0910_TSGENERAL, state->tsgeneral); /* TSGENERAL */
	write_reg(state, RSTV0910_CFGEXT,    0x02); /* CFGEXT */

	if (state->single)
		write_reg(state, RSTV0910_GENCFG, 0x14); /* GENCFG */
	else
		write_reg(state, RSTV0910_GENCFG, 0x15); /* GENCFG */

	write_reg(state, RSTV0910_P1_TNRCFG2, 0x02); /* IQSWAP = 0 */
	write_reg(state, RSTV0910_P2_TNRCFG2, 0x82); /* IQSWAP = 1 */

	write_reg(state, RSTV0910_P1_CAR3CFG, 0x02);
	write_reg(state, RSTV0910_P2_CAR3CFG, 0x02);
	write_reg(state, RSTV0910_P1_DMDCFG4, 0x04);
	write_reg(state, RSTV0910_P2_DMDCFG4, 0x04);

	write_reg(state, RSTV0910_TSTRES0, 0x80); /* LDPC Reset */
	write_reg(state, RSTV0910_TSTRES0, 0x00);

	write_reg(state, RSTV0910_P1_TSPIDFLT1, 0x00);
	write_reg(state, RSTV0910_P2_TSPIDFLT1, 0x00);

	write_reg(state, RSTV0910_P1_TMGCFG2, 0x80);
	write_reg(state, RSTV0910_P2_TMGCFG2, 0x80);

	set_mclock(state, 135000000);

	/* TS output */
	write_reg(state, RSTV0910_P1_TSCFGH, state->tscfgh | 0x01);
	write_reg(state, RSTV0910_P1_TSCFGH, state->tscfgh);
	write_reg(state, RSTV0910_P1_TSCFGM, 0xC0); /* Manual speed */
	write_reg(state, RSTV0910_P1_TSCFGL, 0x20);

	write_reg(state, RSTV0910_P1_TSSPEED, state->tsspeed);

	write_reg(state, RSTV0910_P2_TSCFGH, state->tscfgh | 0x01);
	write_reg(state, RSTV0910_P2_TSCFGH, state->tscfgh);
	write_reg(state, RSTV0910_P2_TSCFGM, 0xC0); /* Manual speed */
	write_reg(state, RSTV0910_P2_TSCFGL, 0x20);

	write_reg(state, RSTV0910_P2_TSSPEED, state->tsspeed);

	/* Reset stream merger */
	write_reg(state, RSTV0910_P1_TSCFGH, state->tscfgh | 0x01);
	write_reg(state, RSTV0910_P2_TSCFGH, state->tscfgh | 0x01);
	write_reg(state, RSTV0910_P1_TSCFGH, state->tscfgh);
	write_reg(state, RSTV0910_P2_TSCFGH, state->tscfgh);

	write_reg(state, RSTV0910_P1_I2CRPT, state->i2crpt);
	write_reg(state, RSTV0910_P2_I2CRPT, state->i2crpt);

	write_reg(state, RSTV0910_P1_TSINSDELM, 0x17);
	write_reg(state, RSTV0910_P1_TSINSDELL, 0xff);

	write_reg(state, RSTV0910_P2_TSINSDELM, 0x17);
	write_reg(state, RSTV0910_P2_TSINSDELL, 0xff);

	init_diseqc(state);
	return 0;
}