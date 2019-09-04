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
struct mxl111sf_state {int dummy; } ;
struct dvb_frontend {struct mxl111sf_demod_state* demodulator_priv; int /*<<< orphan*/  ops; } ;
struct mxl111sf_demod_state {struct dvb_frontend fe; struct mxl111sf_demod_config const* cfg; struct mxl111sf_state* mxl_state; } ;
struct mxl111sf_demod_config {int dummy; } ;
struct dvb_frontend_ops {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mxl111sf_demod_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mxl111sf_demod_ops ; 
 int /*<<< orphan*/  mxl_dbg (char*) ; 

struct dvb_frontend *mxl111sf_demod_attach(struct mxl111sf_state *mxl_state,
				   const struct mxl111sf_demod_config *cfg)
{
	struct mxl111sf_demod_state *state = NULL;

	mxl_dbg("()");

	state = kzalloc(sizeof(struct mxl111sf_demod_state), GFP_KERNEL);
	if (state == NULL)
		return NULL;

	state->mxl_state = mxl_state;
	state->cfg = cfg;

	memcpy(&state->fe.ops, &mxl111sf_demod_ops,
	       sizeof(struct dvb_frontend_ops));

	state->fe.demodulator_priv = state;
	return &state->fe;
}