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

/* Variables and functions */
 int /*<<< orphan*/  BITS_PER_LONG ; 
 int IWL_RATE_INVALID ; 
 int find_last_bit (unsigned long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int rs_get_max_rate_from_mask(unsigned long rate_mask)
{
	if (rate_mask)
		return find_last_bit(&rate_mask, BITS_PER_LONG);
	return IWL_RATE_INVALID;
}