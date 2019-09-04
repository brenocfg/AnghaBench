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
struct dvb_frontend {struct cx22702_state* demodulator_priv; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  inversion; } ;
struct cx22702_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int cx22702_get_tps (struct cx22702_state*,struct dtv_frontend_properties*) ; 
 int cx22702_readreg (struct cx22702_state*,int) ; 

__attribute__((used)) static int cx22702_get_frontend(struct dvb_frontend *fe,
				struct dtv_frontend_properties *c)
{
	struct cx22702_state *state = fe->demodulator_priv;

	u8 reg0C = cx22702_readreg(state, 0x0C);

	c->inversion = reg0C & 0x1 ? INVERSION_ON : INVERSION_OFF;
	return cx22702_get_tps(state, c);
}