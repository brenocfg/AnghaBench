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
typedef  int /*<<< orphan*/  u16 ;
struct status_block_e4 {int dummy; } ;
struct qedf_ctx {int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  cdev; TYPE_2__* pdev; } ;
struct qed_sb_info {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {TYPE_1__* common; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int (* sb_init ) (int /*<<< orphan*/ ,struct qed_sb_info*,struct status_block_e4*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  QED_SB_TYPE_STORAGE ; 
 struct status_block_e4* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* qed_ops ; 
 int stub1 (int /*<<< orphan*/ ,struct qed_sb_info*,struct status_block_e4*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qedf_alloc_and_init_sb(struct qedf_ctx *qedf,
	struct qed_sb_info *sb_info, u16 sb_id)
{
	struct status_block_e4 *sb_virt;
	dma_addr_t sb_phys;
	int ret;

	sb_virt = dma_alloc_coherent(&qedf->pdev->dev,
	    sizeof(struct status_block_e4), &sb_phys, GFP_KERNEL);

	if (!sb_virt) {
		QEDF_ERR(&qedf->dbg_ctx,
			 "Status block allocation failed for id = %d.\n",
			 sb_id);
		return -ENOMEM;
	}

	ret = qed_ops->common->sb_init(qedf->cdev, sb_info, sb_virt, sb_phys,
	    sb_id, QED_SB_TYPE_STORAGE);

	if (ret) {
		QEDF_ERR(&qedf->dbg_ctx,
			 "Status block initialization failed (0x%x) for id = %d.\n",
			 ret, sb_id);
		return ret;
	}

	return 0;
}