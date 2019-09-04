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
struct dvb_frontend {struct cx24120_state* demodulator_priv; } ;
struct dtv_frontend_properties {int frequency; } ;
struct cx24120_state {TYPE_1__* i2c; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CX24120_HAS_LOCK ; 
 int /*<<< orphan*/  CX24120_REG_FREQ1 ; 
 int /*<<< orphan*/  CX24120_REG_FREQ2 ; 
 int /*<<< orphan*/  CX24120_REG_FREQ3 ; 
 int /*<<< orphan*/  CX24120_REG_STATUS ; 
 int /*<<< orphan*/  cx24120_get_fec (struct dvb_frontend*) ; 
 int cx24120_readreg (struct cx24120_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int cx24120_get_frontend(struct dvb_frontend *fe,
				struct dtv_frontend_properties *c)
{
	struct cx24120_state *state = fe->demodulator_priv;
	u8 freq1, freq2, freq3;
	int status;

	dev_dbg(&state->i2c->dev, "\n");

	/* don't return empty data if we're not tuned in */
	status = cx24120_readreg(state, CX24120_REG_STATUS);
	if (!(status & CX24120_HAS_LOCK))
		return 0;

	/* Get frequency */
	freq1 = cx24120_readreg(state, CX24120_REG_FREQ1);
	freq2 = cx24120_readreg(state, CX24120_REG_FREQ2);
	freq3 = cx24120_readreg(state, CX24120_REG_FREQ3);
	c->frequency = (freq3 << 16) | (freq2 << 8) | freq1;
	dev_dbg(&state->i2c->dev, "frequency = %d\n", c->frequency);

	/* Get modulation, fec, pilot */
	cx24120_get_fec(fe);

	return 0;
}