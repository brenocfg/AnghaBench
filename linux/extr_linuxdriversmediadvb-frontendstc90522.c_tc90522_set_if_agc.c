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
struct tc90522_state {int dummy; } ;
struct reg_val {int member_0; int member_1; int val; } ;
struct TYPE_2__ {scalar_t__* delsys; } ;
struct dvb_frontend {TYPE_1__ ops; struct tc90522_state* demodulator_priv; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct reg_val*) ; 
 scalar_t__ SYS_ISDBS ; 
 int reg_write (struct tc90522_state*,struct reg_val*,int) ; 

__attribute__((used)) static int tc90522_set_if_agc(struct dvb_frontend *fe, bool on)
{
	struct reg_val agc_sat[] = {
		{ 0x0a, 0x00 },
		{ 0x10, 0x30 },
		{ 0x11, 0x00 },
		{ 0x03, 0x01 },
	};
	struct reg_val agc_ter[] = {
		{ 0x25, 0x00 },
		{ 0x23, 0x4c },
		{ 0x01, 0x40 },
	};
	struct tc90522_state *state;
	struct reg_val *rv;
	int num;

	state = fe->demodulator_priv;
	if (fe->ops.delsys[0] == SYS_ISDBS) {
		agc_sat[0].val = on ? 0xff : 0x00;
		agc_sat[1].val |= 0x80;
		agc_sat[1].val |= on ? 0x01 : 0x00;
		agc_sat[2].val |= on ? 0x40 : 0x00;
		rv = agc_sat;
		num = ARRAY_SIZE(agc_sat);
	} else {
		agc_ter[0].val = on ? 0x40 : 0x00;
		agc_ter[1].val |= on ? 0x00 : 0x01;
		rv = agc_ter;
		num = ARRAY_SIZE(agc_ter);
	}
	return reg_write(state, rv, num);
}