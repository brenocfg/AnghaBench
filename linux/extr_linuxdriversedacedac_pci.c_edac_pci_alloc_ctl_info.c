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
struct edac_pci_ctl_info {int /*<<< orphan*/  name; int /*<<< orphan*/  op_state; void* pvt_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OP_ALLOC ; 
 void* edac_align_ptr (void**,int,unsigned int) ; 
 int /*<<< orphan*/  edac_dbg (int,char*) ; 
 struct edac_pci_ctl_info* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

struct edac_pci_ctl_info *edac_pci_alloc_ctl_info(unsigned int sz_pvt,
						const char *edac_pci_name)
{
	struct edac_pci_ctl_info *pci;
	void *p = NULL, *pvt;
	unsigned int size;

	edac_dbg(1, "\n");

	pci = edac_align_ptr(&p, sizeof(*pci), 1);
	pvt = edac_align_ptr(&p, 1, sz_pvt);
	size = ((unsigned long)pvt) + sz_pvt;

	/* Alloc the needed control struct memory */
	pci = kzalloc(size, GFP_KERNEL);
	if (pci  == NULL)
		return NULL;

	/* Now much private space */
	pvt = sz_pvt ? ((char *)pci) + ((unsigned long)pvt) : NULL;

	pci->pvt_info = pvt;
	pci->op_state = OP_ALLOC;

	snprintf(pci->name, strlen(edac_pci_name) + 1, "%s", edac_pci_name);

	return pci;
}