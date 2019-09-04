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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_2__ strength; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; } ;
struct TYPE_3__ {int /*<<< orphan*/  uvalue; } ;

/* Variables and functions */

__attribute__((used)) static int mb86a20s_read_signal_strength_from_cache(struct dvb_frontend *fe,
						    u16 *strength)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;


	*strength = c->strength.stat[0].uvalue;

	return 0;
}