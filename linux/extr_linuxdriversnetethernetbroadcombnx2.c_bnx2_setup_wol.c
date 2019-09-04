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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct bnx2 {int advertising; scalar_t__ phy_port; scalar_t__ line_speed; int flags; scalar_t__ fw_last_msg; TYPE_1__* dev; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  phy_lock; scalar_t__ wol; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_Autoneg ; 
 int /*<<< orphan*/  AUTONEG_SPEED ; 
 scalar_t__ BNX2_CHIP (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_5709 ; 
 int BNX2_DRV_MSG_CODE_SUSPEND_NO_WOL ; 
 int BNX2_DRV_MSG_CODE_SUSPEND_WOL ; 
 int BNX2_DRV_MSG_DATA_WAIT3 ; 
 scalar_t__ BNX2_EMAC_MODE ; 
 int BNX2_EMAC_MODE_25G_MODE ; 
 int BNX2_EMAC_MODE_ACPI_RCVD ; 
 int BNX2_EMAC_MODE_MPKT ; 
 int BNX2_EMAC_MODE_MPKT_RCVD ; 
 int BNX2_EMAC_MODE_PORT ; 
 int BNX2_EMAC_MODE_PORT_GMII ; 
 int BNX2_EMAC_MODE_PORT_MII ; 
 scalar_t__ BNX2_EMAC_MULTICAST_HASH0 ; 
 scalar_t__ BNX2_EMAC_RX_MODE ; 
 int BNX2_EMAC_RX_MODE_SORT_MODE ; 
 int BNX2_FLAG_NO_WOL ; 
 scalar_t__ BNX2_MISC_ENABLE_SET_BITS ; 
 int BNX2_MISC_ENABLE_SET_BITS_EMAC_ENABLE ; 
 int BNX2_MISC_ENABLE_SET_BITS_RX_PARSER_MAC_ENABLE ; 
 int BNX2_MISC_ENABLE_SET_BITS_TX_HEADER_Q_ENABLE ; 
 int /*<<< orphan*/  BNX2_PORT_FEATURE ; 
 int BNX2_PORT_FEATURE_ASF_ENABLED ; 
 int BNX2_RD (struct bnx2*,scalar_t__) ; 
 scalar_t__ BNX2_RPM_CONFIG ; 
 int BNX2_RPM_CONFIG_ACPI_ENA ; 
 scalar_t__ BNX2_RPM_SORT_USER0 ; 
 int BNX2_RPM_SORT_USER0_BC_EN ; 
 int BNX2_RPM_SORT_USER0_ENA ; 
 int BNX2_RPM_SORT_USER0_MC_EN ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,scalar_t__,int) ; 
 int NUM_MC_HASH_REGISTERS ; 
 scalar_t__ PORT_TP ; 
 scalar_t__ SPEED_2500 ; 
 int /*<<< orphan*/  bnx2_fw_sync (struct bnx2*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2_set_mac_addr (struct bnx2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2_setup_phy (struct bnx2*,scalar_t__) ; 
 int bnx2_shmem_rd (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2_shmem_wr (struct bnx2*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnx2_setup_wol(struct bnx2 *bp)
{
	int i;
	u32 val, wol_msg;

	if (bp->wol) {
		u32 advertising;
		u8 autoneg;

		autoneg = bp->autoneg;
		advertising = bp->advertising;

		if (bp->phy_port == PORT_TP) {
			bp->autoneg = AUTONEG_SPEED;
			bp->advertising = ADVERTISED_10baseT_Half |
				ADVERTISED_10baseT_Full |
				ADVERTISED_100baseT_Half |
				ADVERTISED_100baseT_Full |
				ADVERTISED_Autoneg;
		}

		spin_lock_bh(&bp->phy_lock);
		bnx2_setup_phy(bp, bp->phy_port);
		spin_unlock_bh(&bp->phy_lock);

		bp->autoneg = autoneg;
		bp->advertising = advertising;

		bnx2_set_mac_addr(bp, bp->dev->dev_addr, 0);

		val = BNX2_RD(bp, BNX2_EMAC_MODE);

		/* Enable port mode. */
		val &= ~BNX2_EMAC_MODE_PORT;
		val |= BNX2_EMAC_MODE_MPKT_RCVD |
		       BNX2_EMAC_MODE_ACPI_RCVD |
		       BNX2_EMAC_MODE_MPKT;
		if (bp->phy_port == PORT_TP) {
			val |= BNX2_EMAC_MODE_PORT_MII;
		} else {
			val |= BNX2_EMAC_MODE_PORT_GMII;
			if (bp->line_speed == SPEED_2500)
				val |= BNX2_EMAC_MODE_25G_MODE;
		}

		BNX2_WR(bp, BNX2_EMAC_MODE, val);

		/* receive all multicast */
		for (i = 0; i < NUM_MC_HASH_REGISTERS; i++) {
			BNX2_WR(bp, BNX2_EMAC_MULTICAST_HASH0 + (i * 4),
				0xffffffff);
		}
		BNX2_WR(bp, BNX2_EMAC_RX_MODE, BNX2_EMAC_RX_MODE_SORT_MODE);

		val = 1 | BNX2_RPM_SORT_USER0_BC_EN | BNX2_RPM_SORT_USER0_MC_EN;
		BNX2_WR(bp, BNX2_RPM_SORT_USER0, 0x0);
		BNX2_WR(bp, BNX2_RPM_SORT_USER0, val);
		BNX2_WR(bp, BNX2_RPM_SORT_USER0, val | BNX2_RPM_SORT_USER0_ENA);

		/* Need to enable EMAC and RPM for WOL. */
		BNX2_WR(bp, BNX2_MISC_ENABLE_SET_BITS,
			BNX2_MISC_ENABLE_SET_BITS_RX_PARSER_MAC_ENABLE |
			BNX2_MISC_ENABLE_SET_BITS_TX_HEADER_Q_ENABLE |
			BNX2_MISC_ENABLE_SET_BITS_EMAC_ENABLE);

		val = BNX2_RD(bp, BNX2_RPM_CONFIG);
		val &= ~BNX2_RPM_CONFIG_ACPI_ENA;
		BNX2_WR(bp, BNX2_RPM_CONFIG, val);

		wol_msg = BNX2_DRV_MSG_CODE_SUSPEND_WOL;
	} else {
			wol_msg = BNX2_DRV_MSG_CODE_SUSPEND_NO_WOL;
	}

	if (!(bp->flags & BNX2_FLAG_NO_WOL)) {
		u32 val;

		wol_msg |= BNX2_DRV_MSG_DATA_WAIT3;
		if (bp->fw_last_msg || BNX2_CHIP(bp) != BNX2_CHIP_5709) {
			bnx2_fw_sync(bp, wol_msg, 1, 0);
			return;
		}
		/* Tell firmware not to power down the PHY yet, otherwise
		 * the chip will take a long time to respond to MMIO reads.
		 */
		val = bnx2_shmem_rd(bp, BNX2_PORT_FEATURE);
		bnx2_shmem_wr(bp, BNX2_PORT_FEATURE,
			      val | BNX2_PORT_FEATURE_ASF_ENABLED);
		bnx2_fw_sync(bp, wol_msg, 1, 0);
		bnx2_shmem_wr(bp, BNX2_PORT_FEATURE, val);
	}

}