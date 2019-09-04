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
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct dib8000_state {int /*<<< orphan*/  tune_state; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CT_DEMOD_START ; 
 int /*<<< orphan*/  FE_STATUS_TUNE_PENDING ; 

__attribute__((used)) static int dib8000_tune_restart_from_demod(struct dvb_frontend *fe)
{
	struct dib8000_state *state = fe->demodulator_priv;

	state->status = FE_STATUS_TUNE_PENDING;
	state->tune_state = CT_DEMOD_START;
	return 0;
}