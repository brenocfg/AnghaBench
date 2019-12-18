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
typedef  int u16 ;
struct nxt200x_state {int dummy; } ;
struct dvb_frontend {struct nxt200x_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  nxt200x_readreg_multibyte (struct nxt200x_state*,int,int*,int) ; 
 int /*<<< orphan*/  nxt200x_writebytes (struct nxt200x_state*,int,int*,int) ; 

__attribute__((used)) static int nxt200x_read_snr(struct dvb_frontend* fe, u16* snr)
{

	struct nxt200x_state* state = fe->demodulator_priv;
	u8 b[2];
	u16 temp = 0, temp2;
	u32 snrdb = 0;

	/* setup to read cluster variance */
	b[0] = 0x00;
	nxt200x_writebytes(state, 0xA1, b, 1);

	/* get multreg val from 0xA6 */
	nxt200x_readreg_multibyte(state, 0xA6, b, 2);

	temp = (b[0] << 8) | b[1];
	temp2 = 0x7FFF - temp;

	/* snr will be in db */
	if (temp2 > 0x7F00)
		snrdb = 1000*24 + ( 1000*(30-24) * ( temp2 - 0x7F00 ) / ( 0x7FFF - 0x7F00 ) );
	else if (temp2 > 0x7EC0)
		snrdb = 1000*18 + ( 1000*(24-18) * ( temp2 - 0x7EC0 ) / ( 0x7F00 - 0x7EC0 ) );
	else if (temp2 > 0x7C00)
		snrdb = 1000*12 + ( 1000*(18-12) * ( temp2 - 0x7C00 ) / ( 0x7EC0 - 0x7C00 ) );
	else
		snrdb = 1000*0 + ( 1000*(12-0) * ( temp2 - 0 ) / ( 0x7C00 - 0 ) );

	/* the value reported back from the frontend will be FFFF=32db 0000=0db */
	*snr = snrdb * (0xFFFF/32000);

	return 0;
}