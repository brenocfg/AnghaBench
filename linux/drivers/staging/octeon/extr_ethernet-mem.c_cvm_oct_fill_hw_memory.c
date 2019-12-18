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
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  cvmx_fpa_free (char*,int,int /*<<< orphan*/ ) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cvm_oct_fill_hw_memory(int pool, int size, int elements)
{
	char *memory;
	char *fpa;
	int freed = elements;

	while (freed) {
		/*
		 * FPA memory must be 128 byte aligned.  Since we are
		 * aligning we need to save the original pointer so we
		 * can feed it to kfree when the memory is returned to
		 * the kernel.
		 *
		 * We allocate an extra 256 bytes to allow for
		 * alignment and space for the original pointer saved
		 * just before the block.
		 */
		memory = kmalloc(size + 256, GFP_ATOMIC);
		if (unlikely(!memory)) {
			pr_warn("Unable to allocate %u bytes for FPA pool %d\n",
				elements * size, pool);
			break;
		}
		fpa = (char *)(((unsigned long)memory + 256) & ~0x7fUL);
		*((char **)fpa - 1) = memory;
		cvmx_fpa_free(fpa, pool, 0);
		freed--;
	}
	return elements - freed;
}