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
typedef  unsigned long u8 ;
struct gp8psk_fe_state {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct dvb_frontend {struct gp8psk_fe_state* demodulator_priv; } ;
struct TYPE_2__ {scalar_t__ (* out ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SET_DN_SWITCH ; 
 int /*<<< orphan*/  SET_LNB_VOLTAGE ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gp8psk_fe_send_legacy_dish_cmd (struct dvb_frontend* fe, unsigned long sw_cmd)
{
	struct gp8psk_fe_state *st = fe->demodulator_priv;
	u8 cmd = sw_cmd & 0x7f;

	if (st->ops->out(st->priv, SET_DN_SWITCH, cmd, 0, NULL, 0))
		return -EINVAL;

	if (st->ops->out(st->priv, SET_LNB_VOLTAGE, !!(sw_cmd & 0x80),
			0, NULL, 0))
		return -EINVAL;

	return 0;
}