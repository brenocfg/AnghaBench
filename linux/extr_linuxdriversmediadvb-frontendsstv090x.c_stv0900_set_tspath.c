#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct stv090x_state {TYPE_2__* config; TYPE_1__* internal; } ;
struct TYPE_4__ {int ts1_mode; int ts2_mode; int ts1_tei; int ts2_tei; scalar_t__ ts1_clk; scalar_t__ ts2_clk; } ;
struct TYPE_3__ {int dev_ver; int mclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  RST_HWARE_FIELD ; 
 int /*<<< orphan*/  STV090x_P1_TSCFGH ; 
 int /*<<< orphan*/  STV090x_P1_TSCFGM ; 
 int /*<<< orphan*/  STV090x_P1_TSSPEED ; 
 int /*<<< orphan*/  STV090x_P2_TSCFGH ; 
 int /*<<< orphan*/  STV090x_P2_TSCFGM ; 
 int /*<<< orphan*/  STV090x_P2_TSSPEED ; 
 int /*<<< orphan*/  STV090x_SETFIELD_Px (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STV090x_TSGENERAL ; 
 int /*<<< orphan*/  STV090x_TSGENERAL1X ; 
#define  STV090x_TSMODE_DVBCI 131 
#define  STV090x_TSMODE_PARALLEL_PUNCTURED 130 
#define  STV090x_TSMODE_SERIAL_CONTINUOUS 129 
#define  STV090x_TSMODE_SERIAL_PUNCTURED 128 
 int /*<<< orphan*/  TSFIFO_DVBCI_FIELD ; 
 int /*<<< orphan*/  TSFIFO_MANSPEED_FIELD ; 
 int /*<<< orphan*/  TSFIFO_SERIAL_FIELD ; 
 int /*<<< orphan*/  TSFIFO_TEIUPDATE_FIELD ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int stv090x_read_reg (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ stv090x_write_reg (struct stv090x_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stv0900_set_tspath(struct stv090x_state *state)
{
	u32 reg;

	if (state->internal->dev_ver >= 0x20) {
		switch (state->config->ts1_mode) {
		case STV090x_TSMODE_PARALLEL_PUNCTURED:
		case STV090x_TSMODE_DVBCI:
			switch (state->config->ts2_mode) {
			case STV090x_TSMODE_SERIAL_PUNCTURED:
			case STV090x_TSMODE_SERIAL_CONTINUOUS:
			default:
				stv090x_write_reg(state, STV090x_TSGENERAL, 0x00);
				break;

			case STV090x_TSMODE_PARALLEL_PUNCTURED:
			case STV090x_TSMODE_DVBCI:
				if (stv090x_write_reg(state, STV090x_TSGENERAL, 0x06) < 0) /* Mux'd stream mode */
					goto err;
				reg = stv090x_read_reg(state, STV090x_P1_TSCFGM);
				STV090x_SETFIELD_Px(reg, TSFIFO_MANSPEED_FIELD, 3);
				if (stv090x_write_reg(state, STV090x_P1_TSCFGM, reg) < 0)
					goto err;
				reg = stv090x_read_reg(state, STV090x_P2_TSCFGM);
				STV090x_SETFIELD_Px(reg, TSFIFO_MANSPEED_FIELD, 3);
				if (stv090x_write_reg(state, STV090x_P2_TSCFGM, reg) < 0)
					goto err;
				if (stv090x_write_reg(state, STV090x_P1_TSSPEED, 0x14) < 0)
					goto err;
				if (stv090x_write_reg(state, STV090x_P2_TSSPEED, 0x28) < 0)
					goto err;
				break;
			}
			break;

		case STV090x_TSMODE_SERIAL_PUNCTURED:
		case STV090x_TSMODE_SERIAL_CONTINUOUS:
		default:
			switch (state->config->ts2_mode) {
			case STV090x_TSMODE_SERIAL_PUNCTURED:
			case STV090x_TSMODE_SERIAL_CONTINUOUS:
			default:
				if (stv090x_write_reg(state, STV090x_TSGENERAL, 0x0c) < 0)
					goto err;
				break;

			case STV090x_TSMODE_PARALLEL_PUNCTURED:
			case STV090x_TSMODE_DVBCI:
				if (stv090x_write_reg(state, STV090x_TSGENERAL, 0x0a) < 0)
					goto err;
				break;
			}
			break;
		}
	} else {
		switch (state->config->ts1_mode) {
		case STV090x_TSMODE_PARALLEL_PUNCTURED:
		case STV090x_TSMODE_DVBCI:
			switch (state->config->ts2_mode) {
			case STV090x_TSMODE_SERIAL_PUNCTURED:
			case STV090x_TSMODE_SERIAL_CONTINUOUS:
			default:
				stv090x_write_reg(state, STV090x_TSGENERAL1X, 0x10);
				break;

			case STV090x_TSMODE_PARALLEL_PUNCTURED:
			case STV090x_TSMODE_DVBCI:
				stv090x_write_reg(state, STV090x_TSGENERAL1X, 0x16);
				reg = stv090x_read_reg(state, STV090x_P1_TSCFGM);
				STV090x_SETFIELD_Px(reg, TSFIFO_MANSPEED_FIELD, 3);
				if (stv090x_write_reg(state, STV090x_P1_TSCFGM, reg) < 0)
					goto err;
				reg = stv090x_read_reg(state, STV090x_P1_TSCFGM);
				STV090x_SETFIELD_Px(reg, TSFIFO_MANSPEED_FIELD, 0);
				if (stv090x_write_reg(state, STV090x_P1_TSCFGM, reg) < 0)
					goto err;
				if (stv090x_write_reg(state, STV090x_P1_TSSPEED, 0x14) < 0)
					goto err;
				if (stv090x_write_reg(state, STV090x_P2_TSSPEED, 0x28) < 0)
					goto err;
				break;
			}
			break;

		case STV090x_TSMODE_SERIAL_PUNCTURED:
		case STV090x_TSMODE_SERIAL_CONTINUOUS:
		default:
			switch (state->config->ts2_mode) {
			case STV090x_TSMODE_SERIAL_PUNCTURED:
			case STV090x_TSMODE_SERIAL_CONTINUOUS:
			default:
				stv090x_write_reg(state, STV090x_TSGENERAL1X, 0x14);
				break;

			case STV090x_TSMODE_PARALLEL_PUNCTURED:
			case STV090x_TSMODE_DVBCI:
				stv090x_write_reg(state, STV090x_TSGENERAL1X, 0x12);
				break;
			}
			break;
		}
	}

	switch (state->config->ts1_mode) {
	case STV090x_TSMODE_PARALLEL_PUNCTURED:
		reg = stv090x_read_reg(state, STV090x_P1_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_TEIUPDATE_FIELD, state->config->ts1_tei);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x00);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x00);
		if (stv090x_write_reg(state, STV090x_P1_TSCFGH, reg) < 0)
			goto err;
		break;

	case STV090x_TSMODE_DVBCI:
		reg = stv090x_read_reg(state, STV090x_P1_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_TEIUPDATE_FIELD, state->config->ts1_tei);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x00);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x01);
		if (stv090x_write_reg(state, STV090x_P1_TSCFGH, reg) < 0)
			goto err;
		break;

	case STV090x_TSMODE_SERIAL_PUNCTURED:
		reg = stv090x_read_reg(state, STV090x_P1_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_TEIUPDATE_FIELD, state->config->ts1_tei);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x01);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x00);
		if (stv090x_write_reg(state, STV090x_P1_TSCFGH, reg) < 0)
			goto err;
		break;

	case STV090x_TSMODE_SERIAL_CONTINUOUS:
		reg = stv090x_read_reg(state, STV090x_P1_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_TEIUPDATE_FIELD, state->config->ts1_tei);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x01);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x01);
		if (stv090x_write_reg(state, STV090x_P1_TSCFGH, reg) < 0)
			goto err;
		break;

	default:
		break;
	}

	switch (state->config->ts2_mode) {
	case STV090x_TSMODE_PARALLEL_PUNCTURED:
		reg = stv090x_read_reg(state, STV090x_P2_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_TEIUPDATE_FIELD, state->config->ts2_tei);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x00);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x00);
		if (stv090x_write_reg(state, STV090x_P2_TSCFGH, reg) < 0)
			goto err;
		break;

	case STV090x_TSMODE_DVBCI:
		reg = stv090x_read_reg(state, STV090x_P2_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_TEIUPDATE_FIELD, state->config->ts2_tei);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x00);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x01);
		if (stv090x_write_reg(state, STV090x_P2_TSCFGH, reg) < 0)
			goto err;
		break;

	case STV090x_TSMODE_SERIAL_PUNCTURED:
		reg = stv090x_read_reg(state, STV090x_P2_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_TEIUPDATE_FIELD, state->config->ts2_tei);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x01);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x00);
		if (stv090x_write_reg(state, STV090x_P2_TSCFGH, reg) < 0)
			goto err;
		break;

	case STV090x_TSMODE_SERIAL_CONTINUOUS:
		reg = stv090x_read_reg(state, STV090x_P2_TSCFGH);
		STV090x_SETFIELD_Px(reg, TSFIFO_TEIUPDATE_FIELD, state->config->ts2_tei);
		STV090x_SETFIELD_Px(reg, TSFIFO_SERIAL_FIELD, 0x01);
		STV090x_SETFIELD_Px(reg, TSFIFO_DVBCI_FIELD, 0x01);
		if (stv090x_write_reg(state, STV090x_P2_TSCFGH, reg) < 0)
			goto err;
		break;

	default:
		break;
	}

	if (state->config->ts1_clk > 0) {
		u32 speed;

		switch (state->config->ts1_mode) {
		case STV090x_TSMODE_PARALLEL_PUNCTURED:
		case STV090x_TSMODE_DVBCI:
		default:
			speed = state->internal->mclk /
				(state->config->ts1_clk / 4);
			if (speed < 0x08)
				speed = 0x08;
			if (speed > 0xFF)
				speed = 0xFF;
			break;
		case STV090x_TSMODE_SERIAL_PUNCTURED:
		case STV090x_TSMODE_SERIAL_CONTINUOUS:
			speed = state->internal->mclk /
				(state->config->ts1_clk / 32);
			if (speed < 0x20)
				speed = 0x20;
			if (speed > 0xFF)
				speed = 0xFF;
			break;
		}
		reg = stv090x_read_reg(state, STV090x_P1_TSCFGM);
		STV090x_SETFIELD_Px(reg, TSFIFO_MANSPEED_FIELD, 3);
		if (stv090x_write_reg(state, STV090x_P1_TSCFGM, reg) < 0)
			goto err;
		if (stv090x_write_reg(state, STV090x_P1_TSSPEED, speed) < 0)
			goto err;
	}

	if (state->config->ts2_clk > 0) {
		u32 speed;

		switch (state->config->ts2_mode) {
		case STV090x_TSMODE_PARALLEL_PUNCTURED:
		case STV090x_TSMODE_DVBCI:
		default:
			speed = state->internal->mclk /
				(state->config->ts2_clk / 4);
			if (speed < 0x08)
				speed = 0x08;
			if (speed > 0xFF)
				speed = 0xFF;
			break;
		case STV090x_TSMODE_SERIAL_PUNCTURED:
		case STV090x_TSMODE_SERIAL_CONTINUOUS:
			speed = state->internal->mclk /
				(state->config->ts2_clk / 32);
			if (speed < 0x20)
				speed = 0x20;
			if (speed > 0xFF)
				speed = 0xFF;
			break;
		}
		reg = stv090x_read_reg(state, STV090x_P2_TSCFGM);
		STV090x_SETFIELD_Px(reg, TSFIFO_MANSPEED_FIELD, 3);
		if (stv090x_write_reg(state, STV090x_P2_TSCFGM, reg) < 0)
			goto err;
		if (stv090x_write_reg(state, STV090x_P2_TSSPEED, speed) < 0)
			goto err;
	}

	reg = stv090x_read_reg(state, STV090x_P2_TSCFGH);
	STV090x_SETFIELD_Px(reg, RST_HWARE_FIELD, 0x01);
	if (stv090x_write_reg(state, STV090x_P2_TSCFGH, reg) < 0)
		goto err;
	STV090x_SETFIELD_Px(reg, RST_HWARE_FIELD, 0x00);
	if (stv090x_write_reg(state, STV090x_P2_TSCFGH, reg) < 0)
		goto err;

	reg = stv090x_read_reg(state, STV090x_P1_TSCFGH);
	STV090x_SETFIELD_Px(reg, RST_HWARE_FIELD, 0x01);
	if (stv090x_write_reg(state, STV090x_P1_TSCFGH, reg) < 0)
		goto err;
	STV090x_SETFIELD_Px(reg, RST_HWARE_FIELD, 0x00);
	if (stv090x_write_reg(state, STV090x_P1_TSCFGH, reg) < 0)
		goto err;

	return 0;
err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}