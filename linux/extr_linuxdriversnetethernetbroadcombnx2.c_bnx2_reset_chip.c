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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct bnx2 {scalar_t__ phy_port; int phy_flags; int flags; int /*<<< orphan*/  phy_lock; } ;

/* Variables and functions */
 scalar_t__ BNX2_CHIP (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_5709 ; 
 scalar_t__ BNX2_CHIP_ID (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_ID_5706_A0 ; 
 scalar_t__ BNX2_CHIP_ID_5706_A1 ; 
 int BNX2_DRV_MSG_DATA_WAIT0 ; 
 int BNX2_DRV_MSG_DATA_WAIT1 ; 
 int /*<<< orphan*/  BNX2_DRV_RESET_SIGNATURE ; 
 int /*<<< orphan*/  BNX2_DRV_RESET_SIGNATURE_MAGIC ; 
 int BNX2_FLAG_USING_MSIX ; 
 int /*<<< orphan*/  BNX2_MISC_COMMAND ; 
 int BNX2_MISC_COMMAND_SW_RESET ; 
 int /*<<< orphan*/  BNX2_MISC_ECO_HW_CTL ; 
 int BNX2_MISC_ECO_HW_CTL_LARGE_GRC_TMOUT_EN ; 
 int /*<<< orphan*/  BNX2_MISC_ID ; 
 int /*<<< orphan*/  BNX2_MISC_VREG_CONTROL ; 
 int /*<<< orphan*/  BNX2_PCICFG_MISC_CONFIG ; 
 int BNX2_PCICFG_MISC_CONFIG_CORE_RST_BSY ; 
 int BNX2_PCICFG_MISC_CONFIG_CORE_RST_REQ ; 
 int BNX2_PCICFG_MISC_CONFIG_REG_WINDOW_ENA ; 
 int BNX2_PCICFG_MISC_CONFIG_TARGET_MB_WORD_SWAP ; 
 int /*<<< orphan*/  BNX2_PCI_SWAP_DIAG0 ; 
 int BNX2_PHY_FLAG_REMOTE_PHY_CAP ; 
 int BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int) ; 
 int EBUSY ; 
 int ENODEV ; 
 int bnx2_alloc_bad_rbuf (struct bnx2*) ; 
 int bnx2_fw_sync (struct bnx2*,int,int,int) ; 
 int /*<<< orphan*/  bnx2_init_fw_cap (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_set_default_remote_link (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_setup_msix_tbl (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_shmem_wr (struct bnx2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2_wait_dma_complete (struct bnx2*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
bnx2_reset_chip(struct bnx2 *bp, u32 reset_code)
{
	u32 val;
	int i, rc = 0;
	u8 old_port;

	/* Wait for the current PCI transaction to complete before
	 * issuing a reset. */
	bnx2_wait_dma_complete(bp);

	/* Wait for the firmware to tell us it is ok to issue a reset. */
	bnx2_fw_sync(bp, BNX2_DRV_MSG_DATA_WAIT0 | reset_code, 1, 1);

	/* Deposit a driver reset signature so the firmware knows that
	 * this is a soft reset. */
	bnx2_shmem_wr(bp, BNX2_DRV_RESET_SIGNATURE,
		      BNX2_DRV_RESET_SIGNATURE_MAGIC);

	/* Do a dummy read to force the chip to complete all current transaction
	 * before we issue a reset. */
	val = BNX2_RD(bp, BNX2_MISC_ID);

	if (BNX2_CHIP(bp) == BNX2_CHIP_5709) {
		BNX2_WR(bp, BNX2_MISC_COMMAND, BNX2_MISC_COMMAND_SW_RESET);
		BNX2_RD(bp, BNX2_MISC_COMMAND);
		udelay(5);

		val = BNX2_PCICFG_MISC_CONFIG_REG_WINDOW_ENA |
		      BNX2_PCICFG_MISC_CONFIG_TARGET_MB_WORD_SWAP;

		BNX2_WR(bp, BNX2_PCICFG_MISC_CONFIG, val);

	} else {
		val = BNX2_PCICFG_MISC_CONFIG_CORE_RST_REQ |
		      BNX2_PCICFG_MISC_CONFIG_REG_WINDOW_ENA |
		      BNX2_PCICFG_MISC_CONFIG_TARGET_MB_WORD_SWAP;

		/* Chip reset. */
		BNX2_WR(bp, BNX2_PCICFG_MISC_CONFIG, val);

		/* Reading back any register after chip reset will hang the
		 * bus on 5706 A0 and A1.  The msleep below provides plenty
		 * of margin for write posting.
		 */
		if ((BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A0) ||
		    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A1))
			msleep(20);

		/* Reset takes approximate 30 usec */
		for (i = 0; i < 10; i++) {
			val = BNX2_RD(bp, BNX2_PCICFG_MISC_CONFIG);
			if ((val & (BNX2_PCICFG_MISC_CONFIG_CORE_RST_REQ |
				    BNX2_PCICFG_MISC_CONFIG_CORE_RST_BSY)) == 0)
				break;
			udelay(10);
		}

		if (val & (BNX2_PCICFG_MISC_CONFIG_CORE_RST_REQ |
			   BNX2_PCICFG_MISC_CONFIG_CORE_RST_BSY)) {
			pr_err("Chip reset did not complete\n");
			return -EBUSY;
		}
	}

	/* Make sure byte swapping is properly configured. */
	val = BNX2_RD(bp, BNX2_PCI_SWAP_DIAG0);
	if (val != 0x01020304) {
		pr_err("Chip not in correct endian mode\n");
		return -ENODEV;
	}

	/* Wait for the firmware to finish its initialization. */
	rc = bnx2_fw_sync(bp, BNX2_DRV_MSG_DATA_WAIT1 | reset_code, 1, 0);
	if (rc)
		return rc;

	spin_lock_bh(&bp->phy_lock);
	old_port = bp->phy_port;
	bnx2_init_fw_cap(bp);
	if ((bp->phy_flags & BNX2_PHY_FLAG_REMOTE_PHY_CAP) &&
	    old_port != bp->phy_port)
		bnx2_set_default_remote_link(bp);
	spin_unlock_bh(&bp->phy_lock);

	if (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A0) {
		/* Adjust the voltage regular to two steps lower.  The default
		 * of this register is 0x0000000e. */
		BNX2_WR(bp, BNX2_MISC_VREG_CONTROL, 0x000000fa);

		/* Remove bad rbuf memory from the free pool. */
		rc = bnx2_alloc_bad_rbuf(bp);
	}

	if (bp->flags & BNX2_FLAG_USING_MSIX) {
		bnx2_setup_msix_tbl(bp);
		/* Prevent MSIX table reads and write from timing out */
		BNX2_WR(bp, BNX2_MISC_ECO_HW_CTL,
			BNX2_MISC_ECO_HW_CTL_LARGE_GRC_TMOUT_EN);
	}

	return rc;
}