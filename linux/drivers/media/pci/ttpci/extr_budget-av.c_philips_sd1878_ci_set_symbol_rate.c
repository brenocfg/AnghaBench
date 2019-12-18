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
struct dvb_frontend {int dummy; } ;
typedef  int ratio ;

/* Variables and functions */
 int /*<<< orphan*/  stv0299_writereg (struct dvb_frontend*,int,int) ; 

__attribute__((used)) static int philips_sd1878_ci_set_symbol_rate(struct dvb_frontend *fe,
		u32 srate, u32 ratio)
{
	u8 aclk = 0;
	u8 bclk = 0;
	u8 m1;

	aclk = 0xb5;
	if (srate < 2000000)
		bclk = 0x86;
	else if (srate < 5000000)
		bclk = 0x89;
	else if (srate < 15000000)
		bclk = 0x8f;
	else if (srate < 45000000)
		bclk = 0x95;

	m1 = 0x14;
	if (srate < 4000000)
		m1 = 0x10;

	stv0299_writereg(fe, 0x0e, 0x23);
	stv0299_writereg(fe, 0x0f, 0x94);
	stv0299_writereg(fe, 0x10, 0x39);
	stv0299_writereg(fe, 0x13, aclk);
	stv0299_writereg(fe, 0x14, bclk);
	stv0299_writereg(fe, 0x15, 0xc9);
	stv0299_writereg(fe, 0x1f, (ratio >> 16) & 0xff);
	stv0299_writereg(fe, 0x20, (ratio >> 8) & 0xff);
	stv0299_writereg(fe, 0x21, (ratio) & 0xf0);
	stv0299_writereg(fe, 0x0f, 0x80 | m1);

	return 0;
}