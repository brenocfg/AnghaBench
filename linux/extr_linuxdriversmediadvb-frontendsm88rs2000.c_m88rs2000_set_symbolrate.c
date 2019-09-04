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
typedef  int u64 ;
typedef  int u32 ;
struct m88rs2000_state {int dummy; } ;
struct dvb_frontend {struct m88rs2000_state* demodulator_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  deb_info (char*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int m88rs2000_get_mclk (struct dvb_frontend*) ; 
 int m88rs2000_writereg (struct m88rs2000_state*,int,int) ; 

__attribute__((used)) static int m88rs2000_set_symbolrate(struct dvb_frontend *fe, u32 srate)
{
	struct m88rs2000_state *state = fe->demodulator_priv;
	int ret;
	u64 temp;
	u32 mclk;
	u8 b[3];

	if ((srate < 1000000) || (srate > 45000000))
		return -EINVAL;

	mclk = m88rs2000_get_mclk(fe);
	if (!mclk)
		return -EINVAL;

	temp = srate / 1000;
	temp *= 1 << 24;

	do_div(temp, mclk);

	b[0] = (u8) (temp >> 16) & 0xff;
	b[1] = (u8) (temp >> 8) & 0xff;
	b[2] = (u8) temp & 0xff;

	ret = m88rs2000_writereg(state, 0x93, b[2]);
	ret |= m88rs2000_writereg(state, 0x94, b[1]);
	ret |= m88rs2000_writereg(state, 0x95, b[0]);

	if (srate > 10000000)
		ret |= m88rs2000_writereg(state, 0xa0, 0x20);
	else
		ret |= m88rs2000_writereg(state, 0xa0, 0x60);

	ret |= m88rs2000_writereg(state, 0xa1, 0xe0);

	if (srate > 12000000)
		ret |= m88rs2000_writereg(state, 0xa3, 0x20);
	else if (srate > 2800000)
		ret |= m88rs2000_writereg(state, 0xa3, 0x98);
	else
		ret |= m88rs2000_writereg(state, 0xa3, 0x90);

	deb_info("m88rs2000: m88rs2000_set_symbolrate\n");
	return ret;
}