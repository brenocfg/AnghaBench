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
struct drmem_lmb {int flags; int /*<<< orphan*/  base_addr; int /*<<< orphan*/  drc_index; } ;

/* Variables and functions */
 int DRCONF_MEM_ASSIGNED ; 
 int EINVAL ; 
 int add_memory (int,int /*<<< orphan*/ ,unsigned long) ; 
 int dlpar_add_device_tree_lmb (struct drmem_lmb*) ; 
 int dlpar_online_lmb (struct drmem_lmb*) ; 
 int /*<<< orphan*/  dlpar_release_drc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlpar_remove_device_tree_lmb (struct drmem_lmb*) ; 
 int memory_add_physaddr_to_nid (int /*<<< orphan*/ ) ; 
 unsigned long memory_block_size_bytes () ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_memory (int,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int dlpar_add_lmb(struct drmem_lmb *lmb)
{
	unsigned long block_sz;
	int nid, rc;

	if (lmb->flags & DRCONF_MEM_ASSIGNED)
		return -EINVAL;

	rc = dlpar_add_device_tree_lmb(lmb);
	if (rc) {
		pr_err("Couldn't update device tree for drc index %x\n",
		       lmb->drc_index);
		dlpar_release_drc(lmb->drc_index);
		return rc;
	}

	block_sz = memory_block_size_bytes();

	/* Find the node id for this address */
	nid = memory_add_physaddr_to_nid(lmb->base_addr);

	/* Add the memory */
	rc = add_memory(nid, lmb->base_addr, block_sz);
	if (rc) {
		dlpar_remove_device_tree_lmb(lmb);
		return rc;
	}

	rc = dlpar_online_lmb(lmb);
	if (rc) {
		remove_memory(nid, lmb->base_addr, block_sz);
		dlpar_remove_device_tree_lmb(lmb);
	} else {
		lmb->flags |= DRCONF_MEM_ASSIGNED;
	}

	return rc;
}