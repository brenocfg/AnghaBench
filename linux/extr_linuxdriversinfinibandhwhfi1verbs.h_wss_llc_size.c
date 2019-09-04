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
struct TYPE_2__ {int x86_cache_size; } ;

/* Variables and functions */
 TYPE_1__ boot_cpu_data ; 

__attribute__((used)) static inline int wss_llc_size(void)
{
	/* assume that the boot CPU value is universal for all CPUs */
	return boot_cpu_data.x86_cache_size;
}