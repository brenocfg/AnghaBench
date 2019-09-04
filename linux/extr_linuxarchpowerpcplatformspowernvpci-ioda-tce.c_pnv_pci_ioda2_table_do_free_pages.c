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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 unsigned long TCE_PCI_READ ; 
 unsigned long TCE_PCI_WRITE ; 
 int /*<<< orphan*/ * __va (unsigned long) ; 
 unsigned long be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (unsigned long) ; 

__attribute__((used)) static void pnv_pci_ioda2_table_do_free_pages(__be64 *addr,
		unsigned long size, unsigned int levels)
{
	const unsigned long addr_ul = (unsigned long) addr &
			~(TCE_PCI_READ | TCE_PCI_WRITE);

	if (levels) {
		long i;
		u64 *tmp = (u64 *) addr_ul;

		for (i = 0; i < size; ++i) {
			unsigned long hpa = be64_to_cpu(tmp[i]);

			if (!(hpa & (TCE_PCI_READ | TCE_PCI_WRITE)))
				continue;

			pnv_pci_ioda2_table_do_free_pages(__va(hpa), size,
					levels - 1);
		}
	}

	free_pages(addr_ul, get_order(size << 3));
}