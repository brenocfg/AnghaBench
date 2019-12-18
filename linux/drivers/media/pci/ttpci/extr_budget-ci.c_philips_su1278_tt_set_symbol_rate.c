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
typedef  int u32 ;
struct dvb_frontend {int dummy; } ;
typedef  int ratio ;

/* Variables and functions */
 int /*<<< orphan*/  stv0299_writereg (struct dvb_frontend*,int,int) ; 

__attribute__((used)) static int philips_su1278_tt_set_symbol_rate(struct dvb_frontend *fe, u32 srate, u32 ratio)
{
	stv0299_writereg(fe, 0x0e, 0x44);
	if (srate >= 10000000) {
		stv0299_writereg(fe, 0x13, 0x97);
		stv0299_writereg(fe, 0x14, 0x95);
		stv0299_writereg(fe, 0x15, 0xc9);
		stv0299_writereg(fe, 0x17, 0x8c);
		stv0299_writereg(fe, 0x1a, 0xfe);
		stv0299_writereg(fe, 0x1c, 0x7f);
		stv0299_writereg(fe, 0x2d, 0x09);
	} else {
		stv0299_writereg(fe, 0x13, 0x99);
		stv0299_writereg(fe, 0x14, 0x8d);
		stv0299_writereg(fe, 0x15, 0xce);
		stv0299_writereg(fe, 0x17, 0x43);
		stv0299_writereg(fe, 0x1a, 0x1d);
		stv0299_writereg(fe, 0x1c, 0x12);
		stv0299_writereg(fe, 0x2d, 0x05);
	}
	stv0299_writereg(fe, 0x0e, 0x23);
	stv0299_writereg(fe, 0x0f, 0x94);
	stv0299_writereg(fe, 0x10, 0x39);
	stv0299_writereg(fe, 0x15, 0xc9);

	stv0299_writereg(fe, 0x1f, (ratio >> 16) & 0xff);
	stv0299_writereg(fe, 0x20, (ratio >> 8) & 0xff);
	stv0299_writereg(fe, 0x21, (ratio) & 0xf0);

	return 0;
}