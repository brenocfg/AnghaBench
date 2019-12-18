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
struct cx24123_state {int dummy; } ;

/* Variables and functions */
 int cx24123_readreg (struct cx24123_state*,int) ; 
 int cx24123_writereg (struct cx24123_state*,int,int) ; 

__attribute__((used)) static int cx24123_repeater_mode(struct cx24123_state *state, u8 mode, u8 start)
{
	u8 r = cx24123_readreg(state, 0x23) & 0x1e;
	if (mode)
		r |= (1 << 6) | (start << 5);
	else
		r |= (1 << 7) | (start);
	return cx24123_writereg(state, 0x23, r);
}