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
 int __machine_arch_type ; 
 int /*<<< orphan*/  arch_decomp_setup () ; 
 int do_decompress (scalar_t__,scalar_t__,unsigned char*,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/  error (char*) ; 
 unsigned long free_mem_end_ptr ; 
 unsigned long free_mem_ptr ; 
 scalar_t__ input_data ; 
 scalar_t__ input_data_end ; 
 unsigned char* output_data ; 
 int /*<<< orphan*/  putstr (char*) ; 

void
decompress_kernel(unsigned long output_start, unsigned long free_mem_ptr_p,
		unsigned long free_mem_ptr_end_p,
		int arch_id)
{
	int ret;

	output_data		= (unsigned char *)output_start;
	free_mem_ptr		= free_mem_ptr_p;
	free_mem_end_ptr	= free_mem_ptr_end_p;
	__machine_arch_type	= arch_id;

	arch_decomp_setup();

	putstr("Uncompressing Linux...");
	ret = do_decompress(input_data, input_data_end - input_data,
			    output_data, error);
	if (ret)
		error("decompressor returned an error");
	else
		putstr(" done, booting the kernel.\n");
}