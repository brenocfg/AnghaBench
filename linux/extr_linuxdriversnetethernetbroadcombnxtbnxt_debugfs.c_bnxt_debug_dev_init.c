#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dentry {int dummy; } ;
struct bnxt_cp_ring_info {int /*<<< orphan*/  dim; } ;
struct bnxt {int cp_nr_rings; struct dentry* debugfs_dim; TYPE_1__** bnapi; void* debugfs_pdev; int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {scalar_t__ rx_ring; struct bnxt_cp_ring_info cp_ring; } ;

/* Variables and functions */
 void* bnxt_debug_mnt ; 
 void* debugfs_create_dir (char const*,void*) ; 
 struct dentry* debugfs_dim_ring_init (int /*<<< orphan*/ *,int,struct dentry*) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,...) ; 

void bnxt_debug_dev_init(struct bnxt *bp)
{
	const char *pname = pci_name(bp->pdev);
	struct dentry *pdevf;
	int i;

	bp->debugfs_pdev = debugfs_create_dir(pname, bnxt_debug_mnt);
	if (bp->debugfs_pdev) {
		pdevf = debugfs_create_dir("dim", bp->debugfs_pdev);
		if (!pdevf) {
			pr_err("failed to create debugfs entry %s/dim\n",
			       pname);
			return;
		}
		bp->debugfs_dim = pdevf;
		/* create files for each rx ring */
		for (i = 0; i < bp->cp_nr_rings; i++) {
			struct bnxt_cp_ring_info *cpr = &bp->bnapi[i]->cp_ring;

			if (cpr && bp->bnapi[i]->rx_ring) {
				pdevf = debugfs_dim_ring_init(&cpr->dim, i,
							      bp->debugfs_dim);
				if (!pdevf)
					pr_err("failed to create debugfs entry %s/dim/%d\n",
					       pname, i);
			}
		}
	} else {
		pr_err("failed to create debugfs entry %s\n", pname);
	}
}