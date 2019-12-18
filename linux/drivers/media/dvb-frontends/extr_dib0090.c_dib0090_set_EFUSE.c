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
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ version; } ;
struct dib0090_state {TYPE_1__ identity; } ;

/* Variables and functions */
 int CAP_VALUE_MAX ; 
 int CAP_VALUE_MIN ; 
 int HR_MAX ; 
 int HR_MIN ; 
 scalar_t__ P1D_E_F ; 
 scalar_t__ P1G ; 
 int POLY_MAX ; 
 int POLY_MIN ; 
 int dib0090_read_reg (struct dib0090_state*,int) ; 
 int /*<<< orphan*/  dib0090_write_reg (struct dib0090_state*,int,int) ; 

__attribute__((used)) static void dib0090_set_EFUSE(struct dib0090_state *state)
{
	u8 c, h, n;
	u16 e2, e4;
	u16 cal;

	e2 = dib0090_read_reg(state, 0x26);
	e4 = dib0090_read_reg(state, 0x28);

	if ((state->identity.version == P1D_E_F) ||
			(state->identity.version == P1G) || (e2 == 0xffff)) {

		dib0090_write_reg(state, 0x22, 0x10);
		cal = (dib0090_read_reg(state, 0x22) >> 6) & 0x3ff;

		if ((cal < 670) || (cal == 1023))
			cal = 850;
		n = 165 - ((cal * 10)>>6) ;
		e2 = e4 = (3<<12) | (34<<6) | (n);
	}

	if (e2 != e4)
		e2 &= e4; /* Remove the redundancy  */

	if (e2 != 0xffff) {
		c = e2 & 0x3f;
		n = (e2 >> 12) & 0xf;
		h = (e2 >> 6) & 0x3f;

		if ((c >= CAP_VALUE_MAX) || (c <= CAP_VALUE_MIN))
			c = 32;
		else
			c += 14;
		if ((h >= HR_MAX) || (h <= HR_MIN))
			h = 34;
		if ((n >= POLY_MAX) || (n <= POLY_MIN))
			n = 3;

		dib0090_write_reg(state, 0x13, (h << 10));
		e2 = (n << 11) | ((h >> 2)<<6) | c;
		dib0090_write_reg(state, 0x2, e2); /* Load the BB_2 */
	}
}