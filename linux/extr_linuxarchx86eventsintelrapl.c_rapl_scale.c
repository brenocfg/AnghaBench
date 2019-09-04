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

/* Variables and functions */
 int NR_RAPL_DOMAINS ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int* rapl_hw_unit ; 

__attribute__((used)) static inline u64 rapl_scale(u64 v, int cfg)
{
	if (cfg > NR_RAPL_DOMAINS) {
		pr_warn("Invalid domain %d, failed to scale data\n", cfg);
		return v;
	}
	/*
	 * scale delta to smallest unit (1/2^32)
	 * users must then scale back: count * 1/(1e9*2^32) to get Joules
	 * or use ldexp(count, -32).
	 * Watts = Joules/Time delta
	 */
	return v << (32 - rapl_hw_unit[cfg - 1]);
}