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
typedef  int u16 ;
struct stv0299_state {int dummy; } ;
struct dvb_frontend {struct stv0299_state* demodulator_priv; } ;
typedef  int s32 ;

/* Variables and functions */
 int stv0299_readreg (struct stv0299_state*,int) ; 

__attribute__((used)) static int stv0299_read_snr(struct dvb_frontend* fe, u16* snr)
{
	struct stv0299_state* state = fe->demodulator_priv;

	s32 xsnr = 0xffff - ((stv0299_readreg (state, 0x24) << 8)
			   | stv0299_readreg (state, 0x25));
	xsnr = 3 * (xsnr - 0xa100);
	*snr = (xsnr > 0xffff) ? 0xffff : (xsnr < 0) ? 0 : xsnr;

	return 0;
}