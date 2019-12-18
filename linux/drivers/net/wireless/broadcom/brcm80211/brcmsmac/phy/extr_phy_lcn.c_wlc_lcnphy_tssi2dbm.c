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
typedef  int s32 ;

/* Variables and functions */

s32 wlc_lcnphy_tssi2dbm(s32 tssi, s32 a1, s32 b0, s32 b1)
{
	s32 a, b, p;

	a = 32768 + (a1 * tssi);
	b = (1024 * b0) + (64 * b1 * tssi);
	p = ((2 * b) + a) / (2 * a);

	return p;
}