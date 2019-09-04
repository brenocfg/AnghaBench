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
struct drmem_lmb {int aa_index; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRCONF_MEM_ASSIGNED ; 
 int drmem_update_dt () ; 
 int rtas_hp_event ; 

__attribute__((used)) static int dlpar_remove_device_tree_lmb(struct drmem_lmb *lmb)
{
	int rc;

	lmb->flags &= ~DRCONF_MEM_ASSIGNED;
	lmb->aa_index = 0xffffffff;

	rtas_hp_event = true;
	rc = drmem_update_dt();
	rtas_hp_event = false;

	return rc;
}