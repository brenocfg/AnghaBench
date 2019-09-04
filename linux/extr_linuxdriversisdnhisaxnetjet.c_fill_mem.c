#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
struct TYPE_3__ {int* s_end; int* send; } ;
struct TYPE_4__ {TYPE_1__ tiger; } ;
struct BCState {TYPE_2__ hw; } ;

/* Variables and functions */

__attribute__((used)) static void fill_mem(struct BCState *bcs, u_int *pos, u_int cnt, int chan, u_char fill)
{
	u_int mask = 0x000000ff, val = 0, *p = pos;
	u_int i;

	val |= fill;
	if (chan) {
		val  <<= 8;
		mask <<= 8;
	}
	mask ^= 0xffffffff;
	for (i = 0; i < cnt; i++) {
		*p &= mask;
		*p++ |= val;
		if (p > bcs->hw.tiger.s_end)
			p = bcs->hw.tiger.send;
	}
}