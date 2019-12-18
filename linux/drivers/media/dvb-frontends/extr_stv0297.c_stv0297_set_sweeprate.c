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
struct stv0297_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stv0297_writereg (struct stv0297_state*,int,long) ; 
 int /*<<< orphan*/  stv0297_writereg_mask (struct stv0297_state*,int,int,long) ; 

__attribute__((used)) static void stv0297_set_sweeprate(struct stv0297_state *state, short fshift, long symrate)
{
	long tmp;

	tmp = (long) fshift *262144L;	/* 262144 = 2*18 */
	tmp /= symrate;
	tmp *= 1024;		/* 1024 = 2*10   */

	// adjust
	if (tmp >= 0) {
		tmp += 500000;
	} else {
		tmp -= 500000;
	}
	tmp /= 1000000;

	stv0297_writereg(state, 0x60, tmp & 0xFF);
	stv0297_writereg_mask(state, 0x69, 0xF0, (tmp >> 4) & 0xf0);
}