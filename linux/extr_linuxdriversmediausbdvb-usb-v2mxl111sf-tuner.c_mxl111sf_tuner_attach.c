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
struct mxl111sf_tuner_state {struct mxl111sf_tuner_config const* cfg; struct mxl111sf_state* mxl_state; } ;
struct mxl111sf_tuner_config {int dummy; } ;
struct mxl111sf_state {int dummy; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_ops; } ;
struct dvb_frontend {struct mxl111sf_tuner_state* tuner_priv; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mxl111sf_tuner_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mxl111sf_tuner_tuner_ops ; 
 int /*<<< orphan*/  mxl_dbg (char*) ; 

struct dvb_frontend *mxl111sf_tuner_attach(struct dvb_frontend *fe,
				struct mxl111sf_state *mxl_state,
				const struct mxl111sf_tuner_config *cfg)
{
	struct mxl111sf_tuner_state *state = NULL;

	mxl_dbg("()");

	state = kzalloc(sizeof(struct mxl111sf_tuner_state), GFP_KERNEL);
	if (state == NULL)
		return NULL;

	state->mxl_state = mxl_state;
	state->cfg = cfg;

	memcpy(&fe->ops.tuner_ops, &mxl111sf_tuner_tuner_ops,
	       sizeof(struct dvb_tuner_ops));

	fe->tuner_priv = state;
	return fe;
}