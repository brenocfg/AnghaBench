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
struct saa7146_pgtable {int nents; int /*<<< orphan*/ * slist; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 long PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int pci_map_sg (struct pci_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_sg (struct pci_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ saa7146_pgtable_alloc (struct pci_dev*,struct saa7146_pgtable*) ; 
 scalar_t__ saa7146_pgtable_build_single (struct pci_dev*,struct saa7146_pgtable*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  saa7146_pgtable_free (struct pci_dev*,struct saa7146_pgtable*) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vmalloc_32 (long) ; 
 int /*<<< orphan*/ * vmalloc_to_sg (void*,int) ; 

void *saa7146_vmalloc_build_pgtable(struct pci_dev *pci, long length, struct saa7146_pgtable *pt)
{
	int pages = (length+PAGE_SIZE-1)/PAGE_SIZE;
	void *mem = vmalloc_32(length);
	int slen = 0;

	if (NULL == mem)
		goto err_null;

	if (!(pt->slist = vmalloc_to_sg(mem, pages)))
		goto err_free_mem;

	if (saa7146_pgtable_alloc(pci, pt))
		goto err_free_slist;

	pt->nents = pages;
	slen = pci_map_sg(pci,pt->slist,pt->nents,PCI_DMA_FROMDEVICE);
	if (0 == slen)
		goto err_free_pgtable;

	if (0 != saa7146_pgtable_build_single(pci, pt, pt->slist, slen))
		goto err_unmap_sg;

	return mem;

err_unmap_sg:
	pci_unmap_sg(pci, pt->slist, pt->nents, PCI_DMA_FROMDEVICE);
err_free_pgtable:
	saa7146_pgtable_free(pci, pt);
err_free_slist:
	kfree(pt->slist);
	pt->slist = NULL;
err_free_mem:
	vfree(mem);
err_null:
	return NULL;
}