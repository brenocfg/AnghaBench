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
struct TYPE_2__ {unsigned long initrd_addr; unsigned long initrd_size; char* cmdline; unsigned long cmdline_len; } ;

/* Variables and functions */
 scalar_t__ _end ; 
 TYPE_1__ loader_info ; 
 int /*<<< orphan*/  simple_alloc_init (scalar_t__,unsigned long,int,int) ; 

void cuboot_init(unsigned long r4, unsigned long r5,
		 unsigned long r6, unsigned long r7,
		 unsigned long end_of_ram)
{
	unsigned long avail_ram = end_of_ram - (unsigned long)_end;

	loader_info.initrd_addr = r4;
	loader_info.initrd_size = r4 ? r5 - r4 : 0;
	loader_info.cmdline = (char *)r6;
	loader_info.cmdline_len = r7 - r6;

	simple_alloc_init(_end, avail_ram - 1024*1024, 32, 64);
}