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
typedef  int u32 ;
struct TYPE_8__ {TYPE_3__* stat; } ;
struct TYPE_6__ {TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_4__ pre_bit_count; TYPE_2__ pre_bit_error; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; } ;
struct TYPE_7__ {int /*<<< orphan*/  uvalue; } ;
struct TYPE_5__ {scalar_t__ scale; int /*<<< orphan*/  uvalue; } ;

/* Variables and functions */
 scalar_t__ FE_SCALE_NOT_AVAILABLE ; 
 int frac_times1e6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drx39xxj_read_ber(struct dvb_frontend *fe, u32 *ber)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;

	if (p->pre_bit_error.stat[0].scale == FE_SCALE_NOT_AVAILABLE) {
		*ber = 0;
		return 0;
	}

	if (!p->pre_bit_count.stat[0].uvalue) {
		if (!p->pre_bit_error.stat[0].uvalue)
			*ber = 0;
		else
			*ber = 1000000;
	} else {
		*ber = frac_times1e6(p->pre_bit_error.stat[0].uvalue,
				     p->pre_bit_count.stat[0].uvalue);
	}
	return 0;
}