#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int flags; TYPE_2__ scache; TYPE_2__ icache; TYPE_2__ dcache; } ;

/* Variables and functions */
 void* CACHE_DESC_SHAPE (TYPE_2__) ; 
 int CPU_HAS_L2_CACHE ; 
 int SH_CACHE_COMBINED ; 
 TYPE_1__ current_cpu_data ; 
 void* l1d_cache_shape ; 
 void* l1i_cache_shape ; 
 int l2_cache_shape ; 

__attribute__((used)) static void detect_cache_shape(void)
{
	l1d_cache_shape = CACHE_DESC_SHAPE(current_cpu_data.dcache);

	if (current_cpu_data.dcache.flags & SH_CACHE_COMBINED)
		l1i_cache_shape = l1d_cache_shape;
	else
		l1i_cache_shape = CACHE_DESC_SHAPE(current_cpu_data.icache);

	if (current_cpu_data.flags & CPU_HAS_L2_CACHE)
		l2_cache_shape = CACHE_DESC_SHAPE(current_cpu_data.scache);
	else
		l2_cache_shape = -1; /* No S-cache */
}