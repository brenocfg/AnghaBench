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
struct atom_clock_dividers {int fb_div; int ref_div; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 rv6xx_calculate_vco_frequency(u32 ref_clock,
						struct atom_clock_dividers *dividers,
						u32 fb_divider_scale)
{
	return ref_clock * ((dividers->fb_div & ~1) << fb_divider_scale) /
		(dividers->ref_div + 1);
}