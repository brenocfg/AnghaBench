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
 scalar_t__ ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ HEAP_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int SZ__bss_start ; 
 int /*<<< orphan*/  __decompress (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ _bss ; 
 scalar_t__ _ebss ; 
 scalar_t__ _end ; 
 int /*<<< orphan*/  error ; 
 scalar_t__ free_mem_end_ptr ; 
 unsigned long free_mem_ptr ; 
 int /*<<< orphan*/  input_data ; 
 int /*<<< orphan*/  input_len ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

unsigned long decompress_kernel(void)
{
	void *output, *kernel_end;

	output = (void *) ALIGN((unsigned long) _end + HEAP_SIZE, PAGE_SIZE);
	kernel_end = output + SZ__bss_start;

#ifdef CONFIG_BLK_DEV_INITRD
	/*
	 * Move the initrd right behind the end of the decompressed
	 * kernel image. This also prevents initrd corruption caused by
	 * bss clearing since kernel_end will always be located behind the
	 * current bss section..
	 */
	if (INITRD_START && INITRD_SIZE && kernel_end > (void *) INITRD_START) {
		memmove(kernel_end, (void *) INITRD_START, INITRD_SIZE);
		INITRD_START = (unsigned long) kernel_end;
	}
#endif

	/*
	 * Clear bss section. free_mem_ptr and free_mem_end_ptr need to be
	 * initialized afterwards since they reside in bss.
	 */
	memset(_bss, 0, _ebss - _bss);
	free_mem_ptr = (unsigned long) _end;
	free_mem_end_ptr = free_mem_ptr + HEAP_SIZE;

	__decompress(input_data, input_len, NULL, NULL, output, 0, NULL, error);
	return (unsigned long) output;
}