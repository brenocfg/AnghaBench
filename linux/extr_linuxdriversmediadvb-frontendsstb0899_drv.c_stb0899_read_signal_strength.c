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
typedef  scalar_t__ u16 ;
struct stb0899_internal {int /*<<< orphan*/  lock; } ;
struct stb0899_state {int delsys; int /*<<< orphan*/  verbose; struct stb0899_internal internal; } ;
struct dvb_frontend {struct stb0899_state* demodulator_priv; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  AGCIQVALUE ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  IF_AGC_GAIN ; 
 int /*<<< orphan*/  STB0899_AGCIQIN ; 
 int STB0899_GETFIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STB0899_READ_S2REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STB0899_S2DEMOD ; 
 int /*<<< orphan*/  STB0899_VSTATUS ; 
#define  SYS_DSS 130 
#define  SYS_DVBS 129 
#define  SYS_DVBS2 128 
 int /*<<< orphan*/  VSTATUS_LOCKEDVIT ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  stb0899_dvbs2rf_tab ; 
 int /*<<< orphan*/  stb0899_dvbsrf_tab ; 
 int /*<<< orphan*/  stb0899_read_reg (struct stb0899_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ stb0899_table_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stb0899_read_signal_strength(struct dvb_frontend *fe, u16 *strength)
{
	struct stb0899_state *state		= fe->demodulator_priv;
	struct stb0899_internal *internal	= &state->internal;

	int val;
	u32 reg;
	*strength = 0;
	switch (state->delsys) {
	case SYS_DVBS:
	case SYS_DSS:
		if (internal->lock) {
			reg  = stb0899_read_reg(state, STB0899_VSTATUS);
			if (STB0899_GETFIELD(VSTATUS_LOCKEDVIT, reg)) {

				reg = stb0899_read_reg(state, STB0899_AGCIQIN);
				val = (s32)(s8)STB0899_GETFIELD(AGCIQVALUE, reg);

				*strength = stb0899_table_lookup(stb0899_dvbsrf_tab, ARRAY_SIZE(stb0899_dvbsrf_tab) - 1, val);
				*strength += 750;
				dprintk(state->verbose, FE_DEBUG, 1, "AGCIQVALUE = 0x%02x, C = %d * 0.1 dBm",
					val & 0xff, *strength);
			}
		}
		break;
	case SYS_DVBS2:
		if (internal->lock) {
			reg = STB0899_READ_S2REG(STB0899_S2DEMOD, IF_AGC_GAIN);
			val = STB0899_GETFIELD(IF_AGC_GAIN, reg);

			*strength = stb0899_table_lookup(stb0899_dvbs2rf_tab, ARRAY_SIZE(stb0899_dvbs2rf_tab) - 1, val);
			*strength += 950;
			dprintk(state->verbose, FE_DEBUG, 1, "IF_AGC_GAIN = 0x%04x, C = %d * 0.1 dBm",
				val & 0x3fff, *strength);
		}
		break;
	default:
		dprintk(state->verbose, FE_DEBUG, 1, "Unsupported delivery system");
		return -EINVAL;
	}

	return 0;
}