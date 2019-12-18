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
struct l64781_state {int dummy; } ;
struct dvb_frontend {struct l64781_state* demodulator_priv; } ;

/* Variables and functions */
 int l64781_readreg (struct l64781_state*,int) ; 

__attribute__((used)) static int l64781_read_ber(struct dvb_frontend* fe, u32* ber)
{
	struct l64781_state* state = fe->demodulator_priv;

	/*   XXX FIXME: set up counting period (reg 0x26...0x28)
	 */
	*ber = l64781_readreg (state, 0x39)
	    | (l64781_readreg (state, 0x3a) << 8);

	return 0;
}