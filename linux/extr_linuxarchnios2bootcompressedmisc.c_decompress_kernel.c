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
 int CONFIG_NIOS2_KERNEL_REGION_BASE ; 
 int CONFIG_NIOS2_MEM_BASE ; 
 scalar_t__ HEAP_SIZE ; 
 int /*<<< orphan*/  _end ; 
 int /*<<< orphan*/  console_init () ; 
 scalar_t__ free_mem_end_ptr ; 
 unsigned long free_mem_ptr ; 
 int /*<<< orphan*/  gunzip () ; 
 int /*<<< orphan*/  makecrc () ; 
 void* output_data ; 
 scalar_t__ output_ptr ; 
 int /*<<< orphan*/  puts (char*) ; 

void decompress_kernel(void)
{
	output_data = (void *) (CONFIG_NIOS2_MEM_BASE |
				CONFIG_NIOS2_KERNEL_REGION_BASE);
	output_ptr = 0;
	free_mem_ptr = (unsigned long)&_end;
	free_mem_end_ptr = free_mem_ptr + HEAP_SIZE;

	console_init();
	makecrc();
	puts("Uncompressing Linux... ");
	gunzip();
	puts("Ok, booting the kernel.\n");
}