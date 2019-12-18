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
typedef  int u16 ;
struct dvb_frontend {struct cx22700_state* demodulator_priv; } ;
struct cx22700_state {int dummy; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int cx22700_readreg (struct cx22700_state*,int) ; 

__attribute__((used)) static int cx22700_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct cx22700_state* state = fe->demodulator_priv;

	u16 rs_ber = (cx22700_readreg (state, 0x0d) << 9)
		   | (cx22700_readreg (state, 0x0e) << 1);
	u8 sync = cx22700_readreg (state, 0x07);

	*status = 0;

	if (rs_ber < 0xff00)
		*status |= FE_HAS_SIGNAL;

	if (sync & 0x20)
		*status |= FE_HAS_CARRIER;

	if (sync & 0x10)
		*status |= FE_HAS_VITERBI;

	if (sync & 0x10)
		*status |= FE_HAS_SYNC;

	if (*status == 0x0f)
		*status |= FE_HAS_LOCK;

	return 0;
}