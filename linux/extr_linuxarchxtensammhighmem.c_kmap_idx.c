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
typedef  enum fixed_addresses { ____Placeholder_fixed_addresses } fixed_addresses ;

/* Variables and functions */
 int DCACHE_N_COLORS ; 
 int KM_TYPE_NR ; 
 int smp_processor_id () ; 

__attribute__((used)) static inline enum fixed_addresses kmap_idx(int type, unsigned long color)
{
	return (type + KM_TYPE_NR * smp_processor_id()) * DCACHE_N_COLORS +
		color;
}