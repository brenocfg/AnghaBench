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
struct dvb_frontend {struct as102_state* demodulator_priv; } ;
struct as102_state {int /*<<< orphan*/  elna_cfg; int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* stream_ctrl ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int as102_fe_ts_bus_ctrl(struct dvb_frontend *fe, int acquire)
{
	struct as102_state *state = fe->demodulator_priv;

	return state->ops->stream_ctrl(state->priv, acquire,
				      state->elna_cfg);
}