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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static unsigned long cs2000_ratio_to_rate(u32 ratio, u32 rate_in)
{
	u64 rate_out;

	/*
	 * ratio = rate_out / rate_in * 2^20
	 *
	 * To avoid over flow, rate_out is u64.
	 * The result should be u32 or unsigned long.
	 */

	rate_out = (u64)ratio * rate_in;
	return rate_out >> 20;
}