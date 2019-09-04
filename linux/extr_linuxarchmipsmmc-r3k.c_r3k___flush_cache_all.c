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
 scalar_t__ KSEG0 ; 
 scalar_t__ dcache_size ; 
 scalar_t__ icache_size ; 
 int /*<<< orphan*/  r3k_flush_dcache_range (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  r3k_flush_icache_range (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void r3k___flush_cache_all(void)
{
	r3k_flush_dcache_range(KSEG0, KSEG0 + dcache_size);
	r3k_flush_icache_range(KSEG0, KSEG0 + icache_size);
}