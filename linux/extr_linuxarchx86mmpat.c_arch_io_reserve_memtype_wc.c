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
typedef  scalar_t__ resource_size_t ;
typedef  enum page_cache_mode { ____Placeholder_page_cache_mode } page_cache_mode ;

/* Variables and functions */
 int _PAGE_CACHE_MODE_WC ; 
 int io_reserve_memtype (scalar_t__,scalar_t__,int*) ; 

int arch_io_reserve_memtype_wc(resource_size_t start, resource_size_t size)
{
	enum page_cache_mode type = _PAGE_CACHE_MODE_WC;

	return io_reserve_memtype(start, start + size, &type);
}