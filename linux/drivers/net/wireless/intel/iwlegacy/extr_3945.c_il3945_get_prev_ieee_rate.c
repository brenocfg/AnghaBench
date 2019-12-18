#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_2__ {size_t prev_ieee; } ;

/* Variables and functions */
 size_t RATE_INVALID ; 
 TYPE_1__* il3945_rates ; 

__attribute__((used)) static inline u8
il3945_get_prev_ieee_rate(u8 rate_idx)
{
	u8 rate = il3945_rates[rate_idx].prev_ieee;

	if (rate == RATE_INVALID)
		rate = rate_idx;
	return rate;
}