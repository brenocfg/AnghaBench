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
typedef  enum fe_sec_voltage { ____Placeholder_fe_sec_voltage } fe_sec_voltage ;
struct TYPE_2__ {scalar_t__ (* out ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int SEC_VOLTAGE_18 ; 
 int /*<<< orphan*/  SET_LNB_VOLTAGE ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gp8psk_fe_set_voltage(struct dvb_frontend *fe,
				 enum fe_sec_voltage voltage)
{
	struct gp8psk_fe_state *st = fe->demodulator_priv;

	if (st->ops->out(st->priv, SET_LNB_VOLTAGE,
			 voltage == SEC_VOLTAGE_18, 0, NULL, 0)) {
		return -EINVAL;
	}
	return 0;
}