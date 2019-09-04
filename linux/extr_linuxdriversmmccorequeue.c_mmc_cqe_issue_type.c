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
struct request {int dummy; } ;
struct mmc_host {int dummy; } ;
typedef  enum mmc_issue_type { ____Placeholder_mmc_issue_type } mmc_issue_type ;

/* Variables and functions */
 int MMC_ISSUE_ASYNC ; 
 int MMC_ISSUE_DCMD ; 
 int MMC_ISSUE_SYNC ; 
#define  REQ_OP_DISCARD 132 
#define  REQ_OP_DRV_IN 131 
#define  REQ_OP_DRV_OUT 130 
#define  REQ_OP_FLUSH 129 
#define  REQ_OP_SECURE_ERASE 128 
 int /*<<< orphan*/  mmc_cqe_can_dcmd (struct mmc_host*) ; 
 int req_op (struct request*) ; 

__attribute__((used)) static enum mmc_issue_type mmc_cqe_issue_type(struct mmc_host *host,
					      struct request *req)
{
	switch (req_op(req)) {
	case REQ_OP_DRV_IN:
	case REQ_OP_DRV_OUT:
	case REQ_OP_DISCARD:
	case REQ_OP_SECURE_ERASE:
		return MMC_ISSUE_SYNC;
	case REQ_OP_FLUSH:
		return mmc_cqe_can_dcmd(host) ? MMC_ISSUE_DCMD : MMC_ISSUE_SYNC;
	default:
		return MMC_ISSUE_ASYNC;
	}
}