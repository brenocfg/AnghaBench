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
typedef  int /*<<< orphan*/  u32 ;
struct io_accel2_cmd {int dummy; } ;
struct ctlr_info {int ioaccel_maxsg; int nr_cmds; int /*<<< orphan*/ * ioaccel2_cmd_pool; int /*<<< orphan*/ * ioaccel2_blockFetchTable; int /*<<< orphan*/  ioaccel2_cmd_pool_dhandle; TYPE_2__* pdev; TYPE_1__* cfgtable; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  io_accel_max_embedded_sg_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IOACCEL2_COMMANDLIST_ALIGNMENT ; 
 int IOACCEL2_MAXSGENTRIES ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hpsa_allocate_ioaccel2_sg_chain_blocks (struct ctlr_info*) ; 
 int /*<<< orphan*/  hpsa_free_ioaccel2_cmd_and_bft (struct ctlr_info*) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hpsa_alloc_ioaccel2_cmd_and_bft(struct ctlr_info *h)
{
	int rc;

	/* Allocate ioaccel2 mode command blocks and block fetch table */

	h->ioaccel_maxsg =
		readl(&(h->cfgtable->io_accel_max_embedded_sg_count));
	if (h->ioaccel_maxsg > IOACCEL2_MAXSGENTRIES)
		h->ioaccel_maxsg = IOACCEL2_MAXSGENTRIES;

	BUILD_BUG_ON(sizeof(struct io_accel2_cmd) %
			IOACCEL2_COMMANDLIST_ALIGNMENT);
	h->ioaccel2_cmd_pool =
		dma_alloc_coherent(&h->pdev->dev,
			h->nr_cmds * sizeof(*h->ioaccel2_cmd_pool),
			&h->ioaccel2_cmd_pool_dhandle, GFP_KERNEL);

	h->ioaccel2_blockFetchTable =
		kmalloc(((h->ioaccel_maxsg + 1) *
				sizeof(u32)), GFP_KERNEL);

	if ((h->ioaccel2_cmd_pool == NULL) ||
		(h->ioaccel2_blockFetchTable == NULL)) {
		rc = -ENOMEM;
		goto clean_up;
	}

	rc = hpsa_allocate_ioaccel2_sg_chain_blocks(h);
	if (rc)
		goto clean_up;

	memset(h->ioaccel2_cmd_pool, 0,
		h->nr_cmds * sizeof(*h->ioaccel2_cmd_pool));
	return 0;

clean_up:
	hpsa_free_ioaccel2_cmd_and_bft(h);
	return rc;
}