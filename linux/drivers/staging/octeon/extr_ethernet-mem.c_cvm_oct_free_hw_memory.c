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
 char* cvmx_fpa_alloc (int) ; 
 int /*<<< orphan*/  cvmx_ptr_to_phys (char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 scalar_t__ phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 

__attribute__((used)) static void cvm_oct_free_hw_memory(int pool, int size, int elements)
{
	char *memory;
	char *fpa;

	do {
		fpa = cvmx_fpa_alloc(pool);
		if (fpa) {
			elements--;
			fpa = (char *)phys_to_virt(cvmx_ptr_to_phys(fpa));
			memory = *((char **)fpa - 1);
			kfree(memory);
		}
	} while (fpa);

	if (elements < 0)
		pr_warn("Freeing of pool %u had too many buffers (%d)\n",
			pool, elements);
	else if (elements > 0)
		pr_warn("Warning: Freeing of pool %u is missing %d buffers\n",
			pool, elements);
}