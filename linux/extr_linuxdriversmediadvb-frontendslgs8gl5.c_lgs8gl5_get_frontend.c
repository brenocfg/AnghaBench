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
struct lgs8gl5_state {int dummy; } ;
struct dvb_frontend {struct lgs8gl5_state* demodulator_priv; } ;
struct dtv_frontend_properties {int bandwidth_hz; int /*<<< orphan*/  hierarchy; int /*<<< orphan*/  modulation; int /*<<< orphan*/  transmission_mode; int /*<<< orphan*/  guard_interval; int /*<<< orphan*/  code_rate_LP; int /*<<< orphan*/  code_rate_HP; int /*<<< orphan*/  inversion; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEC_1_2 ; 
 int /*<<< orphan*/  FEC_7_8 ; 
 int /*<<< orphan*/  GUARD_INTERVAL_1_32 ; 
 int /*<<< orphan*/  HIERARCHY_NONE ; 
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int /*<<< orphan*/  QAM_64 ; 
 int /*<<< orphan*/  REG_INVERSION ; 
 int REG_INVERSION_ON ; 
 int /*<<< orphan*/  TRANSMISSION_MODE_2K ; 
 int lgs8gl5_read_reg (struct lgs8gl5_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lgs8gl5_get_frontend(struct dvb_frontend *fe,
		     struct dtv_frontend_properties *p)
{
	struct lgs8gl5_state *state = fe->demodulator_priv;

	u8 inv = lgs8gl5_read_reg(state, REG_INVERSION);

	p->inversion = (inv & REG_INVERSION_ON) ? INVERSION_ON : INVERSION_OFF;

	p->code_rate_HP = FEC_1_2;
	p->code_rate_LP = FEC_7_8;
	p->guard_interval = GUARD_INTERVAL_1_32;
	p->transmission_mode = TRANSMISSION_MODE_2K;
	p->modulation = QAM_64;
	p->hierarchy = HIERARCHY_NONE;
	p->bandwidth_hz = 8000000;

	return 0;
}