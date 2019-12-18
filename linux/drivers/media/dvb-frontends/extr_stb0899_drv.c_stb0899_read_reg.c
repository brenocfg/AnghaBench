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
struct stb0899_state {int dummy; } ;

/* Variables and functions */
 int _stb0899_read_reg (struct stb0899_state*,unsigned int) ; 

int stb0899_read_reg(struct stb0899_state *state, unsigned int reg)
{
	int result;

	result = _stb0899_read_reg(state, reg);
	/*
	 * Bug ID 9:
	 * access to 0xf2xx/0xf6xx
	 * must be followed by read from 0xf2ff/0xf6ff.
	 */
	if ((reg != 0xf2ff) && (reg != 0xf6ff) &&
	    (((reg & 0xff00) == 0xf200) || ((reg & 0xff00) == 0xf600)))
		_stb0899_read_reg(state, (reg | 0x00ff));

	return result;
}