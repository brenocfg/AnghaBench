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
struct spa {int /*<<< orphan*/  spa_lock; struct ocxl_process_element* spa_mem; } ;
struct ocxl_process_element {int /*<<< orphan*/  tid; } ;
struct ocxl_link {int /*<<< orphan*/  platform_data; struct spa* spa; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int EINVAL ; 
 int SPA_PASID_MAX ; 
 int SPA_PE_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pnv_ocxl_spa_remove_pe_from_cache (int /*<<< orphan*/ ,int) ; 

int ocxl_link_update_pe(void *link_handle, int pasid, __u16 tid)
{
	struct ocxl_link *link = (struct ocxl_link *) link_handle;
	struct spa *spa = link->spa;
	struct ocxl_process_element *pe;
	int pe_handle, rc;

	if (pasid > SPA_PASID_MAX)
		return -EINVAL;

	pe_handle = pasid & SPA_PE_MASK;
	pe = spa->spa_mem + pe_handle;

	mutex_lock(&spa->spa_lock);

	pe->tid = cpu_to_be32(tid);

	/*
	 * The barrier makes sure the PE is updated
	 * before we clear the NPU context cache below, so that the
	 * old PE cannot be reloaded erroneously.
	 */
	mb();

	/*
	 * hook to platform code
	 * On powerpc, the entry needs to be cleared from the context
	 * cache of the NPU.
	 */
	rc = pnv_ocxl_spa_remove_pe_from_cache(link->platform_data, pe_handle);
	WARN_ON(rc);

	mutex_unlock(&spa->spa_lock);
	return rc;
}