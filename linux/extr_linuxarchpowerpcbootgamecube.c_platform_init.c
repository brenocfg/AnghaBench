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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  write; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dtb_start ; 
 scalar_t__ _end ; 
 TYPE_1__ console_ops ; 
 int /*<<< orphan*/  fdt_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_alloc_init (scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  ug_console_write ; 
 scalar_t__ ug_probe () ; 

void platform_init(unsigned long r3, unsigned long r4, unsigned long r5)
{
	u32 heapsize = 16*1024*1024 - (u32)_end;

	simple_alloc_init(_end, heapsize, 32, 64);
	fdt_init(_dtb_start);

	if (ug_probe())
		console_ops.write = ug_console_write;
}