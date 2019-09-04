#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct TYPE_3__ {int /*<<< orphan*/  csum; void* crashkernel_size; void* crashkernel_addr; } ;

/* Variables and functions */
 TYPE_1__ os_info ; 
 int /*<<< orphan*/  os_info_csum (TYPE_1__*) ; 

void os_info_crashkernel_add(unsigned long base, unsigned long size)
{
	os_info.crashkernel_addr = (u64)(unsigned long)base;
	os_info.crashkernel_size = (u64)(unsigned long)size;
	os_info.csum = os_info_csum(&os_info);
}