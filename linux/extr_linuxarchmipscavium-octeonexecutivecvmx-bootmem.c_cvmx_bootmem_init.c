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
struct cvmx_bootmem_desc {int dummy; } ;

/* Variables and functions */
 struct cvmx_bootmem_desc* cvmx_bootmem_desc ; 

int cvmx_bootmem_init(void *mem_desc_ptr)
{
	/* Here we set the global pointer to the bootmem descriptor
	 * block.  This pointer will be used directly, so we will set
	 * it up to be directly usable by the application.  It is set
	 * up as follows for the various runtime/ABI combinations:
	 *
	 * Linux 64 bit: Set XKPHYS bit
	 * Linux 32 bit: use mmap to create mapping, use virtual address
	 * CVMX 64 bit:	 use physical address directly
	 * CVMX 32 bit:	 use physical address directly
	 *
	 * Note that the CVMX environment assumes the use of 1-1 TLB
	 * mappings so that the physical addresses can be used
	 * directly
	 */
	if (!cvmx_bootmem_desc) {
#if   defined(CVMX_ABI_64)
		/* Set XKPHYS bit */
		cvmx_bootmem_desc = cvmx_phys_to_ptr(CAST64(mem_desc_ptr));
#else
		cvmx_bootmem_desc = (struct cvmx_bootmem_desc *) mem_desc_ptr;
#endif
	}

	return 0;
}