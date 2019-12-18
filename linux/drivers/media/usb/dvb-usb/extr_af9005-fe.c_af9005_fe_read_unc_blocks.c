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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/ * release; } ;
struct TYPE_4__ {TYPE_1__ tuner_ops; } ;
struct dvb_frontend {TYPE_2__ ops; struct af9005_fe_state* demodulator_priv; } ;
struct af9005_fe_state {int /*<<< orphan*/  unc; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  af9005_fe_refresh_state (struct dvb_frontend*) ; 

__attribute__((used)) static int af9005_fe_read_unc_blocks(struct dvb_frontend *fe, u32 * unc)
{
	struct af9005_fe_state *state = fe->demodulator_priv;
	if (fe->ops.tuner_ops.release == NULL)
		return -ENODEV;
	af9005_fe_refresh_state(fe);
	*unc = state->unc;
	return 0;
}