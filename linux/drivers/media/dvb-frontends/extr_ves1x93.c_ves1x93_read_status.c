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
struct ves1x93_state {int dummy; } ;
struct dvb_frontend {struct ves1x93_state* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int /*<<< orphan*/  msleep (int) ; 
 int ves1x93_readreg (struct ves1x93_state*,int) ; 

__attribute__((used)) static int ves1x93_read_status(struct dvb_frontend *fe,
			       enum fe_status *status)
{
	struct ves1x93_state* state = fe->demodulator_priv;

	u8 sync = ves1x93_readreg (state, 0x0e);

	/*
	 * The ves1893 sometimes returns sync values that make no sense,
	 * because, e.g., the SIGNAL bit is 0, while some of the higher
	 * bits are 1 (and how can there be a CARRIER w/o a SIGNAL?).
	 * Tests showed that the VITERBI and SYNC bits are returned
	 * reliably, while the SIGNAL and CARRIER bits ar sometimes wrong.
	 * If such a case occurs, we read the value again, until we get a
	 * valid value.
	 */
	int maxtry = 10; /* just for safety - let's not get stuck here */
	while ((sync & 0x03) != 0x03 && (sync & 0x0c) && maxtry--) {
		msleep(10);
		sync = ves1x93_readreg (state, 0x0e);
	}

	*status = 0;

	if (sync & 1)
		*status |= FE_HAS_SIGNAL;

	if (sync & 2)
		*status |= FE_HAS_CARRIER;

	if (sync & 4)
		*status |= FE_HAS_VITERBI;

	if (sync & 8)
		*status |= FE_HAS_SYNC;

	if ((sync & 0x1f) == 0x1f)
		*status |= FE_HAS_LOCK;

	return 0;
}