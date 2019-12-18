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
struct pci_epc_mem {int /*<<< orphan*/  page_size; } ;

/* Variables and functions */
 int fls (size_t) ; 
 int fls64 (size_t) ; 
 unsigned int ilog2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_epc_mem_get_order(struct pci_epc_mem *mem, size_t size)
{
	int order;
	unsigned int page_shift = ilog2(mem->page_size);

	size--;
	size >>= page_shift;
#if BITS_PER_LONG == 32
	order = fls(size);
#else
	order = fls64(size);
#endif
	return order;
}