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
struct stv0297_state {TYPE_1__* config; int /*<<< orphan*/  base_freq; } ;
struct dvb_frontend {struct stv0297_state* demodulator_priv; } ;
struct dtv_frontend_properties {scalar_t__ inversion; int symbol_rate; int /*<<< orphan*/  modulation; int /*<<< orphan*/  fec_inner; int /*<<< orphan*/  frequency; } ;
struct TYPE_2__ {scalar_t__ invert; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEC_NONE ; 
 scalar_t__ INVERSION_OFF ; 
 scalar_t__ INVERSION_ON ; 
 int /*<<< orphan*/  QAM_128 ; 
 int /*<<< orphan*/  QAM_16 ; 
 int /*<<< orphan*/  QAM_256 ; 
 int /*<<< orphan*/  QAM_32 ; 
 int /*<<< orphan*/  QAM_64 ; 
 int stv0297_get_symbolrate (struct stv0297_state*) ; 
 int stv0297_readreg (struct stv0297_state*,int) ; 

__attribute__((used)) static int stv0297_get_frontend(struct dvb_frontend *fe,
				struct dtv_frontend_properties *p)
{
	struct stv0297_state *state = fe->demodulator_priv;
	int reg_00, reg_83;

	reg_00 = stv0297_readreg(state, 0x00);
	reg_83 = stv0297_readreg(state, 0x83);

	p->frequency = state->base_freq;
	p->inversion = (reg_83 & 0x08) ? INVERSION_ON : INVERSION_OFF;
	if (state->config->invert)
		p->inversion = (p->inversion == INVERSION_ON) ? INVERSION_OFF : INVERSION_ON;
	p->symbol_rate = stv0297_get_symbolrate(state) * 1000;
	p->fec_inner = FEC_NONE;

	switch ((reg_00 >> 4) & 0x7) {
	case 0:
		p->modulation = QAM_16;
		break;
	case 1:
		p->modulation = QAM_32;
		break;
	case 2:
		p->modulation = QAM_128;
		break;
	case 3:
		p->modulation = QAM_256;
		break;
	case 4:
		p->modulation = QAM_64;
		break;
	}

	return 0;
}