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
typedef  int u32 ;
struct stv090x_state {TYPE_1__* config; } ;
struct dvb_frontend {struct stv090x_state* demodulator_priv; } ;
typedef  enum fe_sec_mini_cmd { ____Placeholder_fe_sec_mini_cmd } fe_sec_mini_cmd ;
struct TYPE_2__ {scalar_t__ diseqc_envelope_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISEQC_RESET_FIELD ; 
 int /*<<< orphan*/  DISTXCTL ; 
 int /*<<< orphan*/  DISTXDATA ; 
 int /*<<< orphan*/  DISTXSTATUS ; 
 int /*<<< orphan*/  DISTX_MODE_FIELD ; 
 int /*<<< orphan*/  DIS_PRECHARGE_FIELD ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  FIFO_FULL_FIELD ; 
 int SEC_MINI_A ; 
 int STV090x_GETFIELD_Px (int,int /*<<< orphan*/ ) ; 
 int STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STV090x_SETFIELD_Px (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ STV090x_WRITE_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TX_IDLE_FIELD ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int stv090x_send_diseqc_burst(struct dvb_frontend *fe,
				     enum fe_sec_mini_cmd burst)
{
	struct stv090x_state *state = fe->demodulator_priv;
	u32 reg, idle = 0, fifo_full = 1;
	u8 mode, value;
	int i;

	reg = STV090x_READ_DEMOD(state, DISTXCTL);

	if (burst == SEC_MINI_A) {
		mode = (state->config->diseqc_envelope_mode) ? 5 : 3;
		value = 0x00;
	} else {
		mode = (state->config->diseqc_envelope_mode) ? 4 : 2;
		value = 0xFF;
	}

	STV090x_SETFIELD_Px(reg, DISTX_MODE_FIELD, mode);
	STV090x_SETFIELD_Px(reg, DISEQC_RESET_FIELD, 1);
	if (STV090x_WRITE_DEMOD(state, DISTXCTL, reg) < 0)
		goto err;
	STV090x_SETFIELD_Px(reg, DISEQC_RESET_FIELD, 0);
	if (STV090x_WRITE_DEMOD(state, DISTXCTL, reg) < 0)
		goto err;

	STV090x_SETFIELD_Px(reg, DIS_PRECHARGE_FIELD, 1);
	if (STV090x_WRITE_DEMOD(state, DISTXCTL, reg) < 0)
		goto err;

	while (fifo_full) {
		reg = STV090x_READ_DEMOD(state, DISTXSTATUS);
		fifo_full = STV090x_GETFIELD_Px(reg, FIFO_FULL_FIELD);
	}

	if (STV090x_WRITE_DEMOD(state, DISTXDATA, value) < 0)
		goto err;

	reg = STV090x_READ_DEMOD(state, DISTXCTL);
	STV090x_SETFIELD_Px(reg, DIS_PRECHARGE_FIELD, 0);
	if (STV090x_WRITE_DEMOD(state, DISTXCTL, reg) < 0)
		goto err;

	i = 0;

	while ((!idle) && (i < 10)) {
		reg = STV090x_READ_DEMOD(state, DISTXSTATUS);
		idle = STV090x_GETFIELD_Px(reg, TX_IDLE_FIELD);
		msleep(10);
		i++;
	}

	return 0;
err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}