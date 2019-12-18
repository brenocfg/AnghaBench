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
typedef  scalar_t__ u32 ;
struct si2165_state {scalar_t__ ber_prev; } ;
struct TYPE_3__ {TYPE_2__* stat; } ;
struct dtv_frontend_properties {TYPE_1__ post_bit_error; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct si2165_state* demodulator_priv; } ;
struct TYPE_4__ {scalar_t__ scale; scalar_t__ uvalue; } ;

/* Variables and functions */
 scalar_t__ FE_SCALE_COUNTER ; 

__attribute__((used)) static int si2165_read_ber(struct dvb_frontend *fe, u32 *ber)
{
	struct si2165_state *state = fe->demodulator_priv;
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;

	if (c->post_bit_error.stat[0].scale != FE_SCALE_COUNTER) {
		*ber = 0;
		return 0;
	}

	*ber = c->post_bit_error.stat[0].uvalue - state->ber_prev;
	state->ber_prev = c->post_bit_error.stat[0].uvalue;

	return 0;
}