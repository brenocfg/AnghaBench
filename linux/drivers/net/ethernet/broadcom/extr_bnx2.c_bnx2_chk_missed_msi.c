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
typedef  int u32 ;
struct bnx2_napi {scalar_t__ last_status_idx; } ;
struct bnx2 {scalar_t__ idle_chk_status_idx; TYPE_1__* irq_tbl; struct bnx2_napi* bnx2_napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_PCICFG_MSI_CONTROL ; 
 int BNX2_PCICFG_MSI_CONTROL_ENABLE ; 
 int BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bnx2_has_work (struct bnx2_napi*) ; 
 int /*<<< orphan*/  bnx2_msi (int /*<<< orphan*/ ,struct bnx2_napi*) ; 

__attribute__((used)) static void
bnx2_chk_missed_msi(struct bnx2 *bp)
{
	struct bnx2_napi *bnapi = &bp->bnx2_napi[0];
	u32 msi_ctrl;

	if (bnx2_has_work(bnapi)) {
		msi_ctrl = BNX2_RD(bp, BNX2_PCICFG_MSI_CONTROL);
		if (!(msi_ctrl & BNX2_PCICFG_MSI_CONTROL_ENABLE))
			return;

		if (bnapi->last_status_idx == bp->idle_chk_status_idx) {
			BNX2_WR(bp, BNX2_PCICFG_MSI_CONTROL, msi_ctrl &
				~BNX2_PCICFG_MSI_CONTROL_ENABLE);
			BNX2_WR(bp, BNX2_PCICFG_MSI_CONTROL, msi_ctrl);
			bnx2_msi(bp->irq_tbl[0].vector, bnapi);
		}
	}

	bp->idle_chk_status_idx = bnapi->last_status_idx;
}