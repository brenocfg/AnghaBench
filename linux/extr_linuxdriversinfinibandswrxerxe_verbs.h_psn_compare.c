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
typedef  int s32 ;

/* Variables and functions */

__attribute__((used)) static inline int psn_compare(u32 psn_a, u32 psn_b)
{
	s32 diff;

	diff = (psn_a - psn_b) << 8;
	return diff;
}