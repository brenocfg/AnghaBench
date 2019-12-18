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
struct TYPE_5__ {int channel_power; } ;
struct TYPE_6__ {TYPE_1__ dvbs2_signal_info; } ;
struct sx8 {TYPE_2__ signal_info; } ;
struct TYPE_8__ {int len; TYPE_3__* stat; } ;
struct dtv_frontend_properties {TYPE_4__ strength; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct sx8* demodulator_priv; } ;
typedef  int s32 ;
struct TYPE_7__ {int svalue; int /*<<< orphan*/  scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_SCALE_DECIBEL ; 

__attribute__((used)) static int get_strength(struct dvb_frontend *fe)
{
	struct sx8 *state = fe->demodulator_priv;
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	s32 str;

	str = 100000 -
	      (state->signal_info.dvbs2_signal_info.channel_power
	       * 10 + 108750);
	p->strength.len = 1;
	p->strength.stat[0].scale = FE_SCALE_DECIBEL;
	p->strength.stat[0].svalue = str;
	return 0;
}