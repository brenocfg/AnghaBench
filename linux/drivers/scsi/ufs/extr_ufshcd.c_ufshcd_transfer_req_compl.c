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
typedef  unsigned long u32 ;
struct ufs_hba {int quirks; unsigned long outstanding_reqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_UTP_TRANSFER_REQ_DOOR_BELL ; 
 int UFSHCI_QUIRK_SKIP_RESET_INTR_AGGR ; 
 int /*<<< orphan*/  __ufshcd_transfer_req_compl (struct ufs_hba*,unsigned long) ; 
 scalar_t__ ufshcd_is_intr_aggr_allowed (struct ufs_hba*) ; 
 unsigned long ufshcd_readl (struct ufs_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_reset_intr_aggr (struct ufs_hba*) ; 

__attribute__((used)) static void ufshcd_transfer_req_compl(struct ufs_hba *hba)
{
	unsigned long completed_reqs;
	u32 tr_doorbell;

	/* Resetting interrupt aggregation counters first and reading the
	 * DOOR_BELL afterward allows us to handle all the completed requests.
	 * In order to prevent other interrupts starvation the DB is read once
	 * after reset. The down side of this solution is the possibility of
	 * false interrupt if device completes another request after resetting
	 * aggregation and before reading the DB.
	 */
	if (ufshcd_is_intr_aggr_allowed(hba) &&
	    !(hba->quirks & UFSHCI_QUIRK_SKIP_RESET_INTR_AGGR))
		ufshcd_reset_intr_aggr(hba);

	tr_doorbell = ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_DOOR_BELL);
	completed_reqs = tr_doorbell ^ hba->outstanding_reqs;

	__ufshcd_transfer_req_compl(hba, completed_reqs);
}