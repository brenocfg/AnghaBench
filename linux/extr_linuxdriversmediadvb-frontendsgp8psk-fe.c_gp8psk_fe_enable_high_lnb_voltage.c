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
struct gp8psk_fe_state {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct dvb_frontend {struct gp8psk_fe_state* demodulator_priv; } ;
struct TYPE_2__ {int (* out ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  USE_EXTRA_VOLT ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gp8psk_fe_enable_high_lnb_voltage(struct dvb_frontend* fe, long onoff)
{
	struct gp8psk_fe_state *st = fe->demodulator_priv;

	return st->ops->out(st->priv, USE_EXTRA_VOLT, onoff, 0, NULL, 0);
}