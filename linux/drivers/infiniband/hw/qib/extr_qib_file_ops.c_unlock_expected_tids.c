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
struct qib_devdata {int rcvtidcnt; int /*<<< orphan*/  pcidev; struct page** pageshadow; int /*<<< orphan*/  tidinvalid; int /*<<< orphan*/ * physshadow; } ;
struct qib_ctxtdata {int ctxt; struct qib_devdata* dd; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  pci_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_release_user_pages (struct page**,int) ; 

__attribute__((used)) static void unlock_expected_tids(struct qib_ctxtdata *rcd)
{
	struct qib_devdata *dd = rcd->dd;
	int ctxt_tidbase = rcd->ctxt * dd->rcvtidcnt;
	int i, cnt = 0, maxtid = ctxt_tidbase + dd->rcvtidcnt;

	for (i = ctxt_tidbase; i < maxtid; i++) {
		struct page *p = dd->pageshadow[i];
		dma_addr_t phys;

		if (!p)
			continue;

		phys = dd->physshadow[i];
		dd->physshadow[i] = dd->tidinvalid;
		dd->pageshadow[i] = NULL;
		pci_unmap_page(dd->pcidev, phys, PAGE_SIZE,
			       PCI_DMA_FROMDEVICE);
		qib_release_user_pages(&p, 1);
		cnt++;
	}
}