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

/* Variables and functions */
 unsigned int RTSX_PHASE_MAX ; 

__attribute__((used)) static inline u32 test_phase_bit(u32 phase_map, unsigned int bit)
{
	bit %= RTSX_PHASE_MAX;
	return phase_map & (1 << bit);
}