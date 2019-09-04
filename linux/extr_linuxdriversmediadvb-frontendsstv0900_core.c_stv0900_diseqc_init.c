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
struct stv0900_state {int demod; TYPE_1__* config; struct stv0900_internal* internal; } ;
struct stv0900_internal {int dummy; } ;
struct dvb_frontend {struct stv0900_state* demodulator_priv; } ;
typedef  enum fe_stv0900_demod_num { ____Placeholder_fe_stv0900_demod_num } fe_stv0900_demod_num ;
struct TYPE_2__ {int diseqc_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISEQC_RESET ; 
 int /*<<< orphan*/  DISTX_MODE ; 
 int /*<<< orphan*/  stv0900_write_bits (struct stv0900_internal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stv0900_diseqc_init(struct dvb_frontend *fe)
{
	struct stv0900_state *state = fe->demodulator_priv;
	struct stv0900_internal *intp = state->internal;
	enum fe_stv0900_demod_num demod = state->demod;

	stv0900_write_bits(intp, DISTX_MODE, state->config->diseqc_mode);
	stv0900_write_bits(intp, DISEQC_RESET, 1);
	stv0900_write_bits(intp, DISEQC_RESET, 0);

	return 0;
}