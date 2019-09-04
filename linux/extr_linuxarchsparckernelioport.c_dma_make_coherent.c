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
 int /*<<< orphan*/  leon_flush_dcache_all () ; 
 scalar_t__ sparc_cpu_model ; 
 scalar_t__ sparc_leon ; 
 int /*<<< orphan*/  sparc_leon3_snooping_enabled () ; 

__attribute__((used)) static inline void dma_make_coherent(unsigned long pa, unsigned long len)
{
	if (sparc_cpu_model == sparc_leon) {
		if (!sparc_leon3_snooping_enabled())
			leon_flush_dcache_all();
	}
}