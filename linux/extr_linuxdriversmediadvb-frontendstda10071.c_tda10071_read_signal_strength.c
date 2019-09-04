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
typedef  unsigned int u16 ;
struct TYPE_4__ {TYPE_1__* stat; } ;
struct dtv_frontend_properties {TYPE_2__ strength; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; } ;
struct TYPE_3__ {scalar_t__ scale; int /*<<< orphan*/  svalue; } ;

/* Variables and functions */
 scalar_t__ FE_SCALE_DECIBEL ; 
 unsigned int clamp (unsigned int,unsigned int,unsigned int) ; 
 int div_s64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tda10071_read_signal_strength(struct dvb_frontend *fe, u16 *strength)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	unsigned int uitmp;

	if (c->strength.stat[0].scale == FE_SCALE_DECIBEL) {
		uitmp = div_s64(c->strength.stat[0].svalue, 1000) + 256;
		uitmp = clamp(uitmp, 181U, 236U); /* -75dBm - -20dBm */
		/* scale value to 0x0000-0xffff */
		*strength = (uitmp-181) * 0xffff / (236-181);
	} else {
		*strength = 0;
	}
	return 0;
}