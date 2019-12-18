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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DSC_FEC_OVERHEAD_FACTOR ; 
 int /*<<< orphan*/  div_u64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mul_u32_u32 (int /*<<< orphan*/ ,unsigned int) ; 

u32 intel_dp_mode_to_fec_clock(u32 mode_clock)
{
	return div_u64(mul_u32_u32(mode_clock, 1000000U),
		       DP_DSC_FEC_OVERHEAD_FACTOR);
}