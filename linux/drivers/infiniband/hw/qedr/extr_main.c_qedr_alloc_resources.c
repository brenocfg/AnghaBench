#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u16 ;
struct regpair {int dummy; } ;
struct qedr_dev {int num_cnq; struct qedr_cnq* sgid_tbl; struct qedr_cnq* sb_array; struct qedr_cnq* cnq_array; scalar_t__ sb_start; int /*<<< orphan*/  cdev; TYPE_3__* ops; int /*<<< orphan*/  pdev; int /*<<< orphan*/  iwarp_wq; int /*<<< orphan*/  qps; int /*<<< orphan*/  sgid_lock; } ;
struct qedr_cnq {int index; int /*<<< orphan*/  pbl; int /*<<< orphan*/  name; int /*<<< orphan*/ * hw_cons_ptr; TYPE_1__* sb_virt; struct qedr_cnq* sb; struct qedr_dev* dev; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_6__ {TYPE_2__* common; scalar_t__ (* rdma_get_start_sb ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int (* chain_alloc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* chain_free ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/ * pi_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_IWARP (struct qedr_dev*) ; 
 int QEDR_MAX_SGID ; 
 int /*<<< orphan*/  QEDR_MSG_INIT ; 
 int /*<<< orphan*/  QEDR_ROCE_MAX_CNQ_SIZE ; 
 int /*<<< orphan*/  QED_CHAIN_CNT_TYPE_U16 ; 
 int /*<<< orphan*/  QED_CHAIN_MODE_PBL ; 
 int /*<<< orphan*/  QED_CHAIN_USE_TO_CONSUME ; 
 int /*<<< orphan*/  QED_RDMA_MAX_CNQ_SIZE ; 
 size_t QED_ROCE_PROTOCOL_INDEX ; 
 int /*<<< orphan*/  XA_FLAGS_LOCK_IRQ ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qedr_cnq*) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_chain_get_cons_idx (int /*<<< orphan*/ *) ; 
 int qedr_alloc_mem_sb (struct qedr_dev*,struct qedr_cnq*,scalar_t__) ; 
 int /*<<< orphan*/  qedr_free_mem_sb (struct qedr_dev*,struct qedr_cnq*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u32 ; 
 int /*<<< orphan*/  xa_init_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qedr_alloc_resources(struct qedr_dev *dev)
{
	struct qedr_cnq *cnq;
	__le16 *cons_pi;
	u16 n_entries;
	int i, rc;

	dev->sgid_tbl = kcalloc(QEDR_MAX_SGID, sizeof(union ib_gid),
				GFP_KERNEL);
	if (!dev->sgid_tbl)
		return -ENOMEM;

	spin_lock_init(&dev->sgid_lock);

	if (IS_IWARP(dev)) {
		xa_init_flags(&dev->qps, XA_FLAGS_LOCK_IRQ);
		dev->iwarp_wq = create_singlethread_workqueue("qedr_iwarpq");
	}

	/* Allocate Status blocks for CNQ */
	dev->sb_array = kcalloc(dev->num_cnq, sizeof(*dev->sb_array),
				GFP_KERNEL);
	if (!dev->sb_array) {
		rc = -ENOMEM;
		goto err1;
	}

	dev->cnq_array = kcalloc(dev->num_cnq,
				 sizeof(*dev->cnq_array), GFP_KERNEL);
	if (!dev->cnq_array) {
		rc = -ENOMEM;
		goto err2;
	}

	dev->sb_start = dev->ops->rdma_get_start_sb(dev->cdev);

	/* Allocate CNQ PBLs */
	n_entries = min_t(u32, QED_RDMA_MAX_CNQ_SIZE, QEDR_ROCE_MAX_CNQ_SIZE);
	for (i = 0; i < dev->num_cnq; i++) {
		cnq = &dev->cnq_array[i];

		rc = qedr_alloc_mem_sb(dev, &dev->sb_array[i],
				       dev->sb_start + i);
		if (rc)
			goto err3;

		rc = dev->ops->common->chain_alloc(dev->cdev,
						   QED_CHAIN_USE_TO_CONSUME,
						   QED_CHAIN_MODE_PBL,
						   QED_CHAIN_CNT_TYPE_U16,
						   n_entries,
						   sizeof(struct regpair *),
						   &cnq->pbl, NULL);
		if (rc)
			goto err4;

		cnq->dev = dev;
		cnq->sb = &dev->sb_array[i];
		cons_pi = dev->sb_array[i].sb_virt->pi_array;
		cnq->hw_cons_ptr = &cons_pi[QED_ROCE_PROTOCOL_INDEX];
		cnq->index = i;
		sprintf(cnq->name, "qedr%d@pci:%s", i, pci_name(dev->pdev));

		DP_DEBUG(dev, QEDR_MSG_INIT, "cnq[%d].cons=%d\n",
			 i, qed_chain_get_cons_idx(&cnq->pbl));
	}

	return 0;
err4:
	qedr_free_mem_sb(dev, &dev->sb_array[i], dev->sb_start + i);
err3:
	for (--i; i >= 0; i--) {
		dev->ops->common->chain_free(dev->cdev, &dev->cnq_array[i].pbl);
		qedr_free_mem_sb(dev, &dev->sb_array[i], dev->sb_start + i);
	}
	kfree(dev->cnq_array);
err2:
	kfree(dev->sb_array);
err1:
	kfree(dev->sgid_tbl);
	return rc;
}