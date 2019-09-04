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
typedef  unsigned long u64 ;

/* Variables and functions */
 unsigned long __IA64_UNCACHED_OFFSET ; 
 void* __va (unsigned long) ; 

__attribute__((used)) static void *virt_map(u64 address)
{
	if (address & (1UL << 63))
		return (void *) (__IA64_UNCACHED_OFFSET | address);

	return __va(address);
}