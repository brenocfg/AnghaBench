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
struct TYPE_4__ {TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_2__ block_error; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; } ;
struct TYPE_3__ {scalar_t__ scale; int /*<<< orphan*/  uvalue; } ;

/* Variables and functions */
 scalar_t__ FE_SCALE_NOT_AVAILABLE ; 

__attribute__((used)) static int drx39xxj_read_ucblocks(struct dvb_frontend *fe, u32 *ucb)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;

	if (p->block_error.stat[0].scale == FE_SCALE_NOT_AVAILABLE) {
		*ucb = 0;
		return 0;
	}

	*ucb = p->block_error.stat[0].uvalue;
	return 0;
}