#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct dtv_frontend_properties {int frequency; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; } ;

/* Variables and functions */
 int EINVAL ; 
 int IF_FREQUENCYx6 ; 

__attribute__((used)) static int advbt771_samsung_tdtc9251dh0_tuner_calc_regs(struct dvb_frontend *fe, u8 *pllbuf, int buf_len)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 div;
	unsigned char bs = 0;
	unsigned char cp = 0;

	if (buf_len < 5) return -EINVAL;

	div = (((c->frequency + 83333) * 3) / 500000) + IF_FREQUENCYx6;

	if (c->frequency < 150000000)
		cp = 0xB4;
	else if (c->frequency < 173000000)
		cp = 0xBC;
	else if (c->frequency < 250000000)
		cp = 0xB4;
	else if (c->frequency < 400000000)
		cp = 0xBC;
	else if (c->frequency < 420000000)
		cp = 0xF4;
	else if (c->frequency < 470000000)
		cp = 0xFC;
	else if (c->frequency < 600000000)
		cp = 0xBC;
	else if (c->frequency < 730000000)
		cp = 0xF4;
	else
		cp = 0xFC;

	if (c->frequency < 150000000)
		bs = 0x01;
	else if (c->frequency < 173000000)
		bs = 0x01;
	else if (c->frequency < 250000000)
		bs = 0x02;
	else if (c->frequency < 400000000)
		bs = 0x02;
	else if (c->frequency < 420000000)
		bs = 0x02;
	else if (c->frequency < 470000000)
		bs = 0x02;
	else
		bs = 0x08;

	pllbuf[0] = 0x61;
	pllbuf[1] = div >> 8;
	pllbuf[2] = div & 0xff;
	pllbuf[3] = cp;
	pllbuf[4] = bs;

	return 5;
}