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
typedef  int u64 ;
typedef  int u32 ;
struct mmc_request {int /*<<< orphan*/  tag; int /*<<< orphan*/  host; TYPE_1__* data; } ;
struct TYPE_2__ {int flags; scalar_t__ blk_addr; int /*<<< orphan*/  blocks; } ;

/* Variables and functions */
 int CQHCI_ACT (int) ; 
 int CQHCI_BLK_ADDR (int) ; 
 int CQHCI_BLK_COUNT (int /*<<< orphan*/ ) ; 
 int CQHCI_DATA_DIR (int) ; 
 int CQHCI_DATA_TAG (int) ; 
 int CQHCI_END (int) ; 
 int CQHCI_FORCED_PROG (int) ; 
 int CQHCI_INT (int) ; 
 int CQHCI_PRIORITY (int) ; 
 int CQHCI_QBAR (int) ; 
 int CQHCI_REL_WRITE (int) ; 
 int CQHCI_VALID (int) ; 
 int MMC_DATA_DAT_TAG ; 
 int MMC_DATA_FORCED_PRG ; 
 int MMC_DATA_PRIO ; 
 int MMC_DATA_QBR ; 
 int MMC_DATA_READ ; 
 int MMC_DATA_REL_WR ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void cqhci_prep_task_desc(struct mmc_request *mrq,
					u64 *data, bool intr)
{
	u32 req_flags = mrq->data->flags;

	*data = CQHCI_VALID(1) |
		CQHCI_END(1) |
		CQHCI_INT(intr) |
		CQHCI_ACT(0x5) |
		CQHCI_FORCED_PROG(!!(req_flags & MMC_DATA_FORCED_PRG)) |
		CQHCI_DATA_TAG(!!(req_flags & MMC_DATA_DAT_TAG)) |
		CQHCI_DATA_DIR(!!(req_flags & MMC_DATA_READ)) |
		CQHCI_PRIORITY(!!(req_flags & MMC_DATA_PRIO)) |
		CQHCI_QBAR(!!(req_flags & MMC_DATA_QBR)) |
		CQHCI_REL_WRITE(!!(req_flags & MMC_DATA_REL_WR)) |
		CQHCI_BLK_COUNT(mrq->data->blocks) |
		CQHCI_BLK_ADDR((u64)mrq->data->blk_addr);

	pr_debug("%s: cqhci: tag %d task descriptor 0x016%llx\n",
		 mmc_hostname(mrq->host), mrq->tag, (unsigned long long)*data);
}