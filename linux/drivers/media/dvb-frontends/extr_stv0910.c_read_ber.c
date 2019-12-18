#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct stv {int dummy; } ;
struct TYPE_8__ {TYPE_3__* stat; } ;
struct TYPE_6__ {TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_4__ pre_bit_count; TYPE_2__ pre_bit_error; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct stv* demodulator_priv; } ;
struct TYPE_7__ {void* uvalue; void* scale; } ;
struct TYPE_5__ {void* uvalue; void* scale; } ;

/* Variables and functions */
 void* FE_SCALE_COUNTER ; 
 int /*<<< orphan*/  get_bit_error_rate (struct stv*,void**,void**) ; 

__attribute__((used)) static int read_ber(struct dvb_frontend *fe)
{
	struct stv *state = fe->demodulator_priv;
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 n, d;

	get_bit_error_rate(state, &n, &d);

	p->pre_bit_error.stat[0].scale = FE_SCALE_COUNTER;
	p->pre_bit_error.stat[0].uvalue = n;
	p->pre_bit_count.stat[0].scale = FE_SCALE_COUNTER;
	p->pre_bit_count.stat[0].uvalue = d;

	return 0;
}