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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {TYPE_2__* stat; } ;
struct dtv_frontend_properties {TYPE_1__ cnr; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; } ;
struct TYPE_4__ {scalar_t__ scale; int /*<<< orphan*/  svalue; } ;

/* Variables and functions */
 scalar_t__ FE_SCALE_NOT_AVAILABLE ; 
 int /*<<< orphan*/  do_div (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int drx39xxj_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	u64 tmp64;

	if (p->cnr.stat[0].scale == FE_SCALE_NOT_AVAILABLE) {
		*snr = 0;
		return 0;
	}

	tmp64 = p->cnr.stat[0].svalue;
	do_div(tmp64, 10);
	*snr = tmp64;
	return 0;
}