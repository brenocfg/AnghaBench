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
struct tda8083_state {int dummy; } ;
struct dvb_frontend {struct tda8083_state* demodulator_priv; } ;
struct dtv_frontend_properties {int /*<<< orphan*/  fec_inner; int /*<<< orphan*/  inversion; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVERSION_OFF ; 
 int /*<<< orphan*/  INVERSION_ON ; 
 int /*<<< orphan*/  tda8083_get_fec (struct tda8083_state*) ; 
 int tda8083_readreg (struct tda8083_state*,int) ; 

__attribute__((used)) static int tda8083_get_frontend(struct dvb_frontend *fe,
				struct dtv_frontend_properties *p)
{
	struct tda8083_state* state = fe->demodulator_priv;

	/*  FIXME: get symbolrate & frequency offset...*/
	/*p->frequency = ???;*/
	p->inversion = (tda8083_readreg (state, 0x0e) & 0x80) ?
			INVERSION_ON : INVERSION_OFF;
	p->fec_inner = tda8083_get_fec(state);
	/*p->symbol_rate = tda8083_get_symbolrate (state);*/

	return 0;
}