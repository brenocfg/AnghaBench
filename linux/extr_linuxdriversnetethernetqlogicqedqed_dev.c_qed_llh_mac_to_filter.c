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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static void qed_llh_mac_to_filter(u32 *p_high, u32 *p_low,
				  u8 *p_filter)
{
	*p_high = p_filter[1] | (p_filter[0] << 8);
	*p_low = p_filter[5] | (p_filter[4] << 8) |
		 (p_filter[3] << 16) | (p_filter[2] << 24);
}