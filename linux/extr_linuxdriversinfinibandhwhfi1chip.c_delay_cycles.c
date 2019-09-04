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
typedef  int /*<<< orphan*/  u16 ;
struct hfi1_pportdata {int current_egress_rate; } ;

/* Variables and functions */
 int egress_cycles (int,int) ; 

__attribute__((used)) static u16 delay_cycles(struct hfi1_pportdata *ppd, u32 desired_egress_rate,
			u32 dw_len)
{
	u32 delta_cycles;
	u32 current_egress_rate = ppd->current_egress_rate;
	/* rates here are in units of 10^6 bits/sec */

	if (desired_egress_rate == -1)
		return 0; /* shouldn't happen */

	if (desired_egress_rate >= current_egress_rate)
		return 0; /* we can't help go faster, only slower */

	delta_cycles = egress_cycles(dw_len * 4, desired_egress_rate) -
			egress_cycles(dw_len * 4, current_egress_rate);

	return (u16)delta_cycles;
}