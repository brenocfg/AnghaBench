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
typedef  int u32 ;
struct bnx2 {int phy_flags; int flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  phy_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_DRV_ACK_CAP_MB ; 
 int BNX2_DRV_ACK_CAP_SIGNATURE ; 
 int BNX2_FLAG_ASF_ENABLE ; 
 int BNX2_FLAG_CAN_KEEP_VLAN ; 
 int BNX2_FW_CAP_CAN_KEEP_VLAN ; 
 int /*<<< orphan*/  BNX2_FW_CAP_MB ; 
 int BNX2_FW_CAP_REMOTE_PHY_CAPABLE ; 
 int BNX2_FW_CAP_SIGNATURE ; 
 int BNX2_FW_CAP_SIGNATURE_MASK ; 
 int /*<<< orphan*/  BNX2_LINK_STATUS ; 
 int BNX2_LINK_STATUS_SERDES_LINK ; 
 int BNX2_PHY_FLAG_REMOTE_PHY_CAP ; 
 int BNX2_PHY_FLAG_SERDES ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_TP ; 
 int bnx2_shmem_rd (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2_shmem_wr (struct bnx2*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnx2_init_fw_cap(struct bnx2 *bp)
{
	u32 val, sig = 0;

	bp->phy_flags &= ~BNX2_PHY_FLAG_REMOTE_PHY_CAP;
	bp->flags &= ~BNX2_FLAG_CAN_KEEP_VLAN;

	if (!(bp->flags & BNX2_FLAG_ASF_ENABLE))
		bp->flags |= BNX2_FLAG_CAN_KEEP_VLAN;

	val = bnx2_shmem_rd(bp, BNX2_FW_CAP_MB);
	if ((val & BNX2_FW_CAP_SIGNATURE_MASK) != BNX2_FW_CAP_SIGNATURE)
		return;

	if ((val & BNX2_FW_CAP_CAN_KEEP_VLAN) == BNX2_FW_CAP_CAN_KEEP_VLAN) {
		bp->flags |= BNX2_FLAG_CAN_KEEP_VLAN;
		sig |= BNX2_DRV_ACK_CAP_SIGNATURE | BNX2_FW_CAP_CAN_KEEP_VLAN;
	}

	if ((bp->phy_flags & BNX2_PHY_FLAG_SERDES) &&
	    (val & BNX2_FW_CAP_REMOTE_PHY_CAPABLE)) {
		u32 link;

		bp->phy_flags |= BNX2_PHY_FLAG_REMOTE_PHY_CAP;

		link = bnx2_shmem_rd(bp, BNX2_LINK_STATUS);
		if (link & BNX2_LINK_STATUS_SERDES_LINK)
			bp->phy_port = PORT_FIBRE;
		else
			bp->phy_port = PORT_TP;

		sig |= BNX2_DRV_ACK_CAP_SIGNATURE |
		       BNX2_FW_CAP_REMOTE_PHY_CAPABLE;
	}

	if (netif_running(bp->dev) && sig)
		bnx2_shmem_wr(bp, BNX2_DRV_ACK_CAP_MB, sig);
}