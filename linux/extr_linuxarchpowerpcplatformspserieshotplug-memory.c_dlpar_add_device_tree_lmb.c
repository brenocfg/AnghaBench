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
struct drmem_lmb {int aa_index; int /*<<< orphan*/  drc_index; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRCONF_MEM_ASSIGNED ; 
 int drmem_update_dt () ; 
 int lookup_lmb_associativity_index (struct drmem_lmb*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int rtas_hp_event ; 

__attribute__((used)) static int dlpar_add_device_tree_lmb(struct drmem_lmb *lmb)
{
	int rc, aa_index;

	lmb->flags |= DRCONF_MEM_ASSIGNED;

	aa_index = lookup_lmb_associativity_index(lmb);
	if (aa_index < 0) {
		pr_err("Couldn't find associativity index for drc index %x\n",
		       lmb->drc_index);
		return aa_index;
	}

	lmb->aa_index = aa_index;

	rtas_hp_event = true;
	rc = drmem_update_dt();
	rtas_hp_event = false;

	return rc;
}