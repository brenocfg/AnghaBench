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
struct io_accel1_cmd {int dummy; } ;
struct ctlr_info {int ioaccel_maxsg; int nr_cmds; int /*<<< orphan*/ * ioaccel_cmd_pool; int /*<<< orphan*/ * ioaccel1_blockFetchTable; int /*<<< orphan*/  ioaccel_cmd_pool_dhandle; TYPE_2__* pdev; TYPE_1__* cfgtable; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  io_accel_max_embedded_sg_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IOACCEL1_COMMANDLIST_ALIGNMENT ; 
 int IOACCEL1_MAXSGENTRIES ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsa_free_ioaccel1_cmd_and_bft (struct ctlr_info*) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hpsa_alloc_ioaccel1_cmd_and_bft(struct ctlr_info *h)
{
	h->ioaccel_maxsg =
		readl(&(h->cfgtable->io_accel_max_embedded_sg_count));
	if (h->ioaccel_maxsg > IOACCEL1_MAXSGENTRIES)
		h->ioaccel_maxsg = IOACCEL1_MAXSGENTRIES;

	/* Command structures must be aligned on a 128-byte boundary
	 * because the 7 lower bits of the address are used by the
	 * hardware.
	 */
	BUILD_BUG_ON(sizeof(struct io_accel1_cmd) %
			IOACCEL1_COMMANDLIST_ALIGNMENT);
	h->ioaccel_cmd_pool =
		dma_alloc_coherent(&h->pdev->dev,
			h->nr_cmds * sizeof(*h->ioaccel_cmd_pool),
			&h->ioaccel_cmd_pool_dhandle, GFP_KERNEL);

	h->ioaccel1_blockFetchTable =
		kmalloc(((h->ioaccel_maxsg + 1) *
				sizeof(u32)), GFP_KERNEL);

	if ((h->ioaccel_cmd_pool == NULL) ||
		(h->ioaccel1_blockFetchTable == NULL))
		goto clean_up;

	memset(h->ioaccel_cmd_pool, 0,
		h->nr_cmds * sizeof(*h->ioaccel_cmd_pool));
	return 0;

clean_up:
	hpsa_free_ioaccel1_cmd_and_bft(h);
	return -ENOMEM;
}