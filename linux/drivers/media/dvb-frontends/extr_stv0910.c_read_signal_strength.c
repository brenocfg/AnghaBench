#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_6__ {TYPE_2__* stat; } ;
struct dtv_frontend_properties {TYPE_3__ strength; } ;
struct TYPE_4__ {struct dtv_frontend_properties dtv_property_cache; } ;
struct stv {scalar_t__ regoff; TYPE_1__ fe; } ;
struct dvb_frontend {struct stv* demodulator_priv; } ;
typedef  int s32 ;
struct TYPE_5__ {int svalue; int /*<<< orphan*/  scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FE_SCALE_DECIBEL ; 
 scalar_t__ RSTV0910_P2_AGCIQIN1 ; 
 scalar_t__ RSTV0910_P2_POWERI ; 
 int /*<<< orphan*/  padc_lookup ; 
 int /*<<< orphan*/  read_regs (struct stv*,scalar_t__,int*,int) ; 
 int table_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void read_signal_strength(struct dvb_frontend *fe)
{
	struct stv *state = fe->demodulator_priv;
	struct dtv_frontend_properties *p = &state->fe.dtv_property_cache;
	u8 reg[2];
	u16 agc;
	s32 padc, power = 0;
	int i;

	read_regs(state, RSTV0910_P2_AGCIQIN1 + state->regoff, reg, 2);

	agc = (((u32)reg[0]) << 8) | reg[1];

	for (i = 0; i < 5; i += 1) {
		read_regs(state, RSTV0910_P2_POWERI + state->regoff, reg, 2);
		power += (u32)reg[0] * (u32)reg[0]
			+ (u32)reg[1] * (u32)reg[1];
		usleep_range(3000, 4000);
	}
	power /= 5;

	padc = table_lookup(padc_lookup, ARRAY_SIZE(padc_lookup), power) + 352;

	p->strength.stat[0].scale = FE_SCALE_DECIBEL;
	p->strength.stat[0].svalue = (padc - agc);
}