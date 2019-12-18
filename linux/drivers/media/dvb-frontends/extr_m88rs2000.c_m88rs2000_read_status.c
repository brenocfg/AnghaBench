#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct m88rs2000_state {TYPE_1__* config; } ;
struct dvb_frontend {struct m88rs2000_state* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_ts_params ) (struct dvb_frontend*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_IS_READ ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int m88rs2000_readreg (struct m88rs2000_state*,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m88rs2000_read_status(struct dvb_frontend *fe,
				 enum fe_status *status)
{
	struct m88rs2000_state *state = fe->demodulator_priv;
	u8 reg = m88rs2000_readreg(state, 0x8c);

	*status = 0;

	if ((reg & 0xee) == 0xee) {
		*status = FE_HAS_CARRIER | FE_HAS_SIGNAL | FE_HAS_VITERBI
			| FE_HAS_SYNC | FE_HAS_LOCK;
		if (state->config->set_ts_params)
			state->config->set_ts_params(fe, CALL_IS_READ);
	}
	return 0;
}