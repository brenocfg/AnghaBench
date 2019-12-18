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
struct qedr_dev {TYPE_1__* pdev; int /*<<< orphan*/  cdev; TYPE_3__* ops; } ;
struct qed_sb_info {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {TYPE_2__* common; } ;
struct TYPE_5__ {int (* sb_init ) (int /*<<< orphan*/ ,struct qed_sb_info*,struct status_block_e4*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QED_SB_TYPE_CNQ ; 
 struct status_block_e4* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,struct status_block_e4*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int stub1 (int /*<<< orphan*/ ,struct qed_sb_info*,struct status_block_e4*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qedr_alloc_mem_sb(struct qedr_dev *dev,
			     struct qed_sb_info *sb_info, u16 sb_id)
{
	struct status_block_e4 *sb_virt;
	dma_addr_t sb_phys;
	int rc;

	sb_virt = dma_alloc_coherent(&dev->pdev->dev,
				     sizeof(*sb_virt), &sb_phys, GFP_KERNEL);
	if (!sb_virt)
		return -ENOMEM;

	rc = dev->ops->common->sb_init(dev->cdev, sb_info,
				       sb_virt, sb_phys, sb_id,
				       QED_SB_TYPE_CNQ);
	if (rc) {
		pr_err("Status block initialization failed\n");
		dma_free_coherent(&dev->pdev->dev, sizeof(*sb_virt),
				  sb_virt, sb_phys);
		return rc;
	}

	return 0;
}