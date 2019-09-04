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
struct stv0367ter_state {int pBER; } ;
struct stv0367_state {struct stv0367ter_state* ter_state; } ;
struct dvb_frontend {struct stv0367_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  F367TER_SFEC_ERR_CNT ; 
 int /*<<< orphan*/  F367TER_SFEC_ERR_CNT_HI ; 
 int /*<<< orphan*/  F367TER_SFEC_ERR_CNT_LO ; 
 int /*<<< orphan*/  F367TER_SFEC_ERR_SOURCE ; 
 int /*<<< orphan*/  F367TER_SFEC_NUM_EVENT ; 
 int /*<<< orphan*/  F367TER_SFERRC_OLDVALUE ; 
 int stv0367_readbits (struct stv0367_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv0367ter_read_ber(struct dvb_frontend *fe, u32 *ber)
{
	struct stv0367_state *state = fe->demodulator_priv;
	struct stv0367ter_state *ter_state = state->ter_state;
	u32 Errors = 0, tber = 0, temporary = 0;
	int abc = 0, def = 0;


	/*wait for counting completion*/
	if (stv0367_readbits(state, F367TER_SFERRC_OLDVALUE) == 0)
		Errors = ((u32)stv0367_readbits(state, F367TER_SFEC_ERR_CNT)
			* (1 << 16))
			+ ((u32)stv0367_readbits(state, F367TER_SFEC_ERR_CNT_HI)
			* (1 << 8))
			+ ((u32)stv0367_readbits(state,
						F367TER_SFEC_ERR_CNT_LO));
	/*measurement not completed, load previous value*/
	else {
		tber = ter_state->pBER;
		return 0;
	}

	abc = stv0367_readbits(state, F367TER_SFEC_ERR_SOURCE);
	def = stv0367_readbits(state, F367TER_SFEC_NUM_EVENT);

	if (Errors == 0) {
		tber = 0;
	} else if (abc == 0x7) {
		if (Errors <= 4) {
			temporary = (Errors * 1000000000) / (8 * (1 << 14));
		} else if (Errors <= 42) {
			temporary = (Errors * 100000000) / (8 * (1 << 14));
			temporary = temporary * 10;
		} else if (Errors <= 429) {
			temporary = (Errors * 10000000) / (8 * (1 << 14));
			temporary = temporary * 100;
		} else if (Errors <= 4294) {
			temporary = (Errors * 1000000) / (8 * (1 << 14));
			temporary = temporary * 1000;
		} else if (Errors <= 42949) {
			temporary = (Errors * 100000) / (8 * (1 << 14));
			temporary = temporary * 10000;
		} else if (Errors <= 429496) {
			temporary = (Errors * 10000) / (8 * (1 << 14));
			temporary = temporary * 100000;
		} else { /*if (Errors<4294967) 2^22 max error*/
			temporary = (Errors * 1000) / (8 * (1 << 14));
			temporary = temporary * 100000;	/* still to *10 */
		}

		/* Byte error*/
		if (def == 2)
			/*tber=Errors/(8*(1 <<14));*/
			tber = temporary;
		else if (def == 3)
			/*tber=Errors/(8*(1 <<16));*/
			tber = temporary / 4;
		else if (def == 4)
			/*tber=Errors/(8*(1 <<18));*/
			tber = temporary / 16;
		else if (def == 5)
			/*tber=Errors/(8*(1 <<20));*/
			tber = temporary / 64;
		else if (def == 6)
			/*tber=Errors/(8*(1 <<22));*/
			tber = temporary / 256;
		else
			/* should not pass here*/
			tber = 0;

		if ((Errors < 4294967) && (Errors > 429496))
			tber *= 10;

	}

	/* save actual value */
	ter_state->pBER = tber;

	(*ber) = tber;

	return 0;
}