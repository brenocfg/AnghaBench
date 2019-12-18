#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct rvu_work {int dummy; } ;
struct rvu {int /*<<< orphan*/  flr_lock; TYPE_2__* flr_wrk; int /*<<< orphan*/  flr_wq; int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; TYPE_1__* hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  work; struct rvu* rvu; } ;
struct TYPE_3__ {int total_pfs; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  BLKADDR_RVUM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RVU_PRIV_PFX_CFG (int) ; 
 int WQ_HIGHPRI ; 
 int WQ_MEM_RECLAIM ; 
 int WQ_UNBOUND ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int,int) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 TYPE_2__* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int pci_sriov_get_totalvfs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_flr_handler ; 
 int rvu_read64 (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rvu_flr_init(struct rvu *rvu)
{
	int dev, num_devs;
	u64 cfg;
	int pf;

	/* Enable FLR for all PFs*/
	for (pf = 0; pf < rvu->hw->total_pfs; pf++) {
		cfg = rvu_read64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_CFG(pf));
		rvu_write64(rvu, BLKADDR_RVUM, RVU_PRIV_PFX_CFG(pf),
			    cfg | BIT_ULL(22));
	}

	rvu->flr_wq = alloc_workqueue("rvu_afpf_flr",
				      WQ_UNBOUND | WQ_HIGHPRI | WQ_MEM_RECLAIM,
				       1);
	if (!rvu->flr_wq)
		return -ENOMEM;

	num_devs = rvu->hw->total_pfs + pci_sriov_get_totalvfs(rvu->pdev);
	rvu->flr_wrk = devm_kcalloc(rvu->dev, num_devs,
				    sizeof(struct rvu_work), GFP_KERNEL);
	if (!rvu->flr_wrk) {
		destroy_workqueue(rvu->flr_wq);
		return -ENOMEM;
	}

	for (dev = 0; dev < num_devs; dev++) {
		rvu->flr_wrk[dev].rvu = rvu;
		INIT_WORK(&rvu->flr_wrk[dev].work, rvu_flr_handler);
	}

	mutex_init(&rvu->flr_lock);

	return 0;
}