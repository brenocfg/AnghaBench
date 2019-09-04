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
struct s921_state {int dummy; } ;
struct dvb_frontend {struct s921_state* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int s921_readreg (struct s921_state*,int) ; 

__attribute__((used)) static int s921_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct s921_state *state = fe->demodulator_priv;
	int regstatus, rc;

	*status = 0;

	rc = s921_readreg(state, 0x81);
	if (rc < 0)
		return rc;

	regstatus = rc << 8;

	rc = s921_readreg(state, 0x82);
	if (rc < 0)
		return rc;

	regstatus |= rc;

	dprintk("status = %04x\n", regstatus);

	/* Full Sync - We don't know what each bit means on regs 0x81/0x82 */
	if ((regstatus & 0xff) == 0x40) {
		*status = FE_HAS_SIGNAL  |
			  FE_HAS_CARRIER |
			  FE_HAS_VITERBI |
			  FE_HAS_SYNC    |
			  FE_HAS_LOCK;
	} else if (regstatus & 0x40) {
		/* This is close to Full Sync, but not enough to get useful info */
		*status = FE_HAS_SIGNAL  |
			  FE_HAS_CARRIER |
			  FE_HAS_VITERBI |
			  FE_HAS_SYNC;
	}

	return 0;
}