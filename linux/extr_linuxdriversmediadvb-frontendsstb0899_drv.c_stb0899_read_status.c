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
typedef  int /*<<< orphan*/  u8 ;
struct stb0899_internal {int /*<<< orphan*/  lock; } ;
struct stb0899_state {int delsys; int /*<<< orphan*/  verbose; struct stb0899_internal internal; } ;
struct dvb_frontend {struct stb0899_state* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEPTED_STREAM ; 
 int /*<<< orphan*/  CFGPDELSTATUS_LOCK ; 
 int /*<<< orphan*/  CONTINUOUS_STREAM ; 
 int /*<<< orphan*/  CSM_LOCK ; 
 int /*<<< orphan*/  DMD_STAT2 ; 
 int EINVAL ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int /*<<< orphan*/  STB0899_CFGPDELSTATUS1 ; 
 int /*<<< orphan*/  STB0899_GETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STB0899_PLPARM ; 
 int /*<<< orphan*/  STB0899_POSTPROC_GPIO_LOCK ; 
 int /*<<< orphan*/  STB0899_READ_S2REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STB0899_S2DEMOD ; 
 int /*<<< orphan*/  STB0899_VSTATUS ; 
#define  SYS_DSS 130 
#define  SYS_DVBS 129 
#define  SYS_DVBS2 128 
 int /*<<< orphan*/  UWP_LOCK ; 
 int /*<<< orphan*/  VITCURPUN ; 
 int /*<<< orphan*/  VSTATUS_LOCKEDVIT ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  stb0899_postproc (struct stb0899_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stb0899_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct stb0899_state *state		= fe->demodulator_priv;
	struct stb0899_internal *internal	= &state->internal;
	u8 reg;
	*status = 0;

	switch (state->delsys) {
	case SYS_DVBS:
	case SYS_DSS:
		dprintk(state->verbose, FE_DEBUG, 1, "Delivery system DVB-S/DSS");
		if (internal->lock) {
			reg  = stb0899_read_reg(state, STB0899_VSTATUS);
			if (STB0899_GETFIELD(VSTATUS_LOCKEDVIT, reg)) {
				dprintk(state->verbose, FE_DEBUG, 1, "--------> FE_HAS_CARRIER | FE_HAS_LOCK");
				*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER | FE_HAS_LOCK;

				reg = stb0899_read_reg(state, STB0899_PLPARM);
				if (STB0899_GETFIELD(VITCURPUN, reg)) {
					dprintk(state->verbose, FE_DEBUG, 1, "--------> FE_HAS_VITERBI | FE_HAS_SYNC");
					*status |= FE_HAS_VITERBI | FE_HAS_SYNC;
					/* post process event */
					stb0899_postproc(state, STB0899_POSTPROC_GPIO_LOCK, 1);
				}
			}
		}
		break;
	case SYS_DVBS2:
		dprintk(state->verbose, FE_DEBUG, 1, "Delivery system DVB-S2");
		if (internal->lock) {
			reg = STB0899_READ_S2REG(STB0899_S2DEMOD, DMD_STAT2);
			if (STB0899_GETFIELD(UWP_LOCK, reg) && STB0899_GETFIELD(CSM_LOCK, reg)) {
				*status |= FE_HAS_CARRIER;
				dprintk(state->verbose, FE_DEBUG, 1,
					"UWP & CSM Lock ! ---> DVB-S2 FE_HAS_CARRIER");

				reg = stb0899_read_reg(state, STB0899_CFGPDELSTATUS1);
				if (STB0899_GETFIELD(CFGPDELSTATUS_LOCK, reg)) {
					*status |= FE_HAS_LOCK;
					dprintk(state->verbose, FE_DEBUG, 1,
						"Packet Delineator Locked ! -----> DVB-S2 FE_HAS_LOCK");

				}
				if (STB0899_GETFIELD(CONTINUOUS_STREAM, reg)) {
					*status |= FE_HAS_VITERBI;
					dprintk(state->verbose, FE_DEBUG, 1,
						"Packet Delineator found VITERBI ! -----> DVB-S2 FE_HAS_VITERBI");
				}
				if (STB0899_GETFIELD(ACCEPTED_STREAM, reg)) {
					*status |= FE_HAS_SYNC;
					dprintk(state->verbose, FE_DEBUG, 1,
						"Packet Delineator found SYNC ! -----> DVB-S2 FE_HAS_SYNC");
					/* post process event */
					stb0899_postproc(state, STB0899_POSTPROC_GPIO_LOCK, 1);
				}
			}
		}
		break;
	default:
		dprintk(state->verbose, FE_DEBUG, 1, "Unsupported delivery system");
		return -EINVAL;
	}
	return 0;
}