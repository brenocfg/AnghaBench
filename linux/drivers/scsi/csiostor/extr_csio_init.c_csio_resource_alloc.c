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
struct csio_wrm {scalar_t__ num_q; } ;
struct csio_rnode {int dummy; } ;
struct csio_mb {int dummy; } ;
struct csio_hw {int /*<<< orphan*/ * mb_mempool; int /*<<< orphan*/ * rnode_mempool; int /*<<< orphan*/  scsi_dma_pool; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CSIO_HW_NEQ ; 
 scalar_t__ CSIO_HW_NFLQ ; 
 scalar_t__ CSIO_HW_NINTXQ ; 
 scalar_t__ CSIO_HW_NIQ ; 
 int CSIO_MAX_SCSI_QSETS ; 
 int /*<<< orphan*/  CSIO_MIN_MEMPOOL_SZ ; 
 int /*<<< orphan*/  CSIO_SCSI_RSP_LEN ; 
 int ENOMEM ; 
 struct csio_wrm* csio_hw_to_wrm (struct csio_hw*) ; 
 int /*<<< orphan*/  dma_pool_create (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* mempool_create_kmalloc_pool (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
csio_resource_alloc(struct csio_hw *hw)
{
	struct csio_wrm *wrm = csio_hw_to_wrm(hw);
	int rv = -ENOMEM;

	wrm->num_q = ((CSIO_MAX_SCSI_QSETS * 2) + CSIO_HW_NIQ +
		       CSIO_HW_NEQ + CSIO_HW_NFLQ + CSIO_HW_NINTXQ);

	hw->mb_mempool = mempool_create_kmalloc_pool(CSIO_MIN_MEMPOOL_SZ,
						  sizeof(struct csio_mb));
	if (!hw->mb_mempool)
		goto err;

	hw->rnode_mempool = mempool_create_kmalloc_pool(CSIO_MIN_MEMPOOL_SZ,
						     sizeof(struct csio_rnode));
	if (!hw->rnode_mempool)
		goto err_free_mb_mempool;

	hw->scsi_dma_pool = dma_pool_create("csio_scsi_dma_pool",
					    &hw->pdev->dev, CSIO_SCSI_RSP_LEN,
					    8, 0);
	if (!hw->scsi_dma_pool)
		goto err_free_rn_pool;

	return 0;

err_free_rn_pool:
	mempool_destroy(hw->rnode_mempool);
	hw->rnode_mempool = NULL;
err_free_mb_mempool:
	mempool_destroy(hw->mb_mempool);
	hw->mb_mempool = NULL;
err:
	return rv;
}