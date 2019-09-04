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
struct sp8870_state {int dummy; } ;
struct dvb_frontend {struct sp8870_state* demodulator_priv; } ;

/* Variables and functions */
 int EIO ; 
 int sp8870_readreg (struct sp8870_state*,int) ; 

__attribute__((used)) static int sp8870_read_uncorrected_blocks (struct dvb_frontend* fe, u32* ublocks)
{
	struct sp8870_state* state = fe->demodulator_priv;
	int ret;

	*ublocks = 0;

	ret = sp8870_readreg(state, 0xC0C);
	if (ret < 0)
		return -EIO;

	if (ret == 0xFFFF)
		ret = ~0;

	*ublocks = ret;

	return 0;
}