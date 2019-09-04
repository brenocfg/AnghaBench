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
struct qm1d1b0004_state {int /*<<< orphan*/  cfg; } ;
struct dvb_frontend {struct qm1d1b0004_state* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 

__attribute__((used)) static int qm1d1b0004_set_config(struct dvb_frontend *fe, void *priv_cfg)
{
	struct qm1d1b0004_state *state;

	state = fe->tuner_priv;
	memcpy(&state->cfg, priv_cfg, sizeof(state->cfg));
	return 0;
}