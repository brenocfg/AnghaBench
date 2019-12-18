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
struct t10_alua_lu_gp_member {int /*<<< orphan*/  lu_gp_mem_lock; struct t10_alua_lu_gp* lu_gp; scalar_t__ lu_gp_assoc; int /*<<< orphan*/  lu_gp_mem_list; int /*<<< orphan*/  lu_gp_mem_ref_cnt; } ;
struct t10_alua_lu_gp {int /*<<< orphan*/  lu_gp_lock; int /*<<< orphan*/  lu_gp_members; } ;
struct se_device {struct t10_alua_lu_gp_member* dev_alua_lu_gp_mem; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct t10_alua_lu_gp_member*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t10_alua_lu_gp_mem_cache ; 

void core_alua_free_lu_gp_mem(struct se_device *dev)
{
	struct t10_alua_lu_gp *lu_gp;
	struct t10_alua_lu_gp_member *lu_gp_mem;

	lu_gp_mem = dev->dev_alua_lu_gp_mem;
	if (!lu_gp_mem)
		return;

	while (atomic_read(&lu_gp_mem->lu_gp_mem_ref_cnt))
		cpu_relax();

	spin_lock(&lu_gp_mem->lu_gp_mem_lock);
	lu_gp = lu_gp_mem->lu_gp;
	if (lu_gp) {
		spin_lock(&lu_gp->lu_gp_lock);
		if (lu_gp_mem->lu_gp_assoc) {
			list_del(&lu_gp_mem->lu_gp_mem_list);
			lu_gp->lu_gp_members--;
			lu_gp_mem->lu_gp_assoc = 0;
		}
		spin_unlock(&lu_gp->lu_gp_lock);
		lu_gp_mem->lu_gp = NULL;
	}
	spin_unlock(&lu_gp_mem->lu_gp_mem_lock);

	kmem_cache_free(t10_alua_lu_gp_mem_cache, lu_gp_mem);
}