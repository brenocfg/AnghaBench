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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct statistics_block {int dummy; } ;
struct pci_dev {scalar_t__ pm_cap; scalar_t__ subsystem_vendor; int subsystem_device; int revision; int /*<<< orphan*/  dev; scalar_t__ msi_cap; scalar_t__ msix_cap; } ;
struct net_device {int /*<<< orphan*/  features; } ;
struct TYPE_3__ {int max_iscsi_conn; } ;
struct TYPE_4__ {int /*<<< orphan*/  expires; } ;
struct bnx2 {int flags; int phy_flags; scalar_t__ pm_cap; int chip_id; scalar_t__ pcix_cap; int func; int shmem_base; char* fw_version; int wol; int* mac_addr; int tx_quick_cons_trip_int; int tx_quick_cons_trip; int tx_ticks_int; int tx_ticks; int rx_quick_cons_trip_int; int rx_quick_cons_trip; int rx_ticks_int; int rx_ticks; int stats_ticks; int phy_addr; int req_flow_ctrl; int /*<<< orphan*/  temp_stats_blk; int /*<<< orphan*/ * regview; int /*<<< orphan*/  cnic_probe; TYPE_1__ cnic_eth_dev; TYPE_2__ timer; int /*<<< orphan*/  cmd_ticks; int /*<<< orphan*/  cmd_ticks_int; int /*<<< orphan*/  com_ticks; int /*<<< orphan*/  com_ticks_int; int /*<<< orphan*/  comp_prod_trip; int /*<<< orphan*/  comp_prod_trip_int; struct pci_dev* pdev; int /*<<< orphan*/  phy_port; int /*<<< orphan*/  current_interval; int /*<<< orphan*/  tx_ring_size; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  cnic_lock; int /*<<< orphan*/  indirect_lock; int /*<<< orphan*/  phy_lock; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2_BC_STATE_CONDITION ; 
 scalar_t__ BNX2_CHIP (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_5706 ; 
 scalar_t__ BNX2_CHIP_5708 ; 
 scalar_t__ BNX2_CHIP_5709 ; 
 int BNX2_CHIP_BOND (struct bnx2*) ; 
 int BNX2_CHIP_BOND_SERDES_BIT ; 
 scalar_t__ BNX2_CHIP_ID (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_ID_5706_A0 ; 
 scalar_t__ BNX2_CHIP_ID_5706_A1 ; 
 scalar_t__ BNX2_CHIP_ID_5708_A0 ; 
 scalar_t__ BNX2_CHIP_ID_5708_B0 ; 
 scalar_t__ BNX2_CHIP_ID_5708_B1 ; 
 scalar_t__ BNX2_CHIP_REV (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_REV_Ax ; 
 scalar_t__ BNX2_CHIP_REV_Bx ; 
 int BNX2_CONDITION_MFW_RUN_MASK ; 
 int BNX2_CONDITION_MFW_RUN_NONE ; 
 int BNX2_CONDITION_MFW_RUN_UNKNOWN ; 
 int /*<<< orphan*/  BNX2_DEV_INFO_BC_REV ; 
 int /*<<< orphan*/  BNX2_DEV_INFO_SIGNATURE ; 
 int BNX2_DEV_INFO_SIGNATURE_MAGIC ; 
 int BNX2_DEV_INFO_SIGNATURE_MAGIC_MASK ; 
 int BNX2_FLAG_AER_ENABLED ; 
 int BNX2_FLAG_ASF_ENABLE ; 
 int BNX2_FLAG_BROKEN_STATS ; 
 int BNX2_FLAG_JUMBO_BROKEN ; 
 int BNX2_FLAG_MSIX_CAP ; 
 int BNX2_FLAG_MSI_CAP ; 
 int BNX2_FLAG_NO_WOL ; 
 int BNX2_FLAG_PCIE ; 
 int BNX2_FLAG_PCIX ; 
 int BNX2_HC_STATS_TICKS_HC_STAT_TICKS ; 
 int /*<<< orphan*/  BNX2_ISCSI_INITIATOR ; 
 int BNX2_ISCSI_INITIATOR_EN ; 
 int /*<<< orphan*/  BNX2_ISCSI_MAX_CONN ; 
 int BNX2_ISCSI_MAX_CONN_MASK ; 
 int BNX2_ISCSI_MAX_CONN_SHIFT ; 
 int /*<<< orphan*/  BNX2_MAX_TX_DESC_CNT ; 
 int BNX2_MCP_TOE_ID ; 
 int BNX2_MCP_TOE_ID_FUNCTION_ID ; 
 int /*<<< orphan*/  BNX2_MFW_VER_PTR ; 
 int /*<<< orphan*/  BNX2_MISC_ID ; 
 int /*<<< orphan*/  BNX2_PCICFG_MISC_CONFIG ; 
 int BNX2_PCICFG_MISC_CONFIG_REG_WINDOW_ENA ; 
 int BNX2_PCICFG_MISC_CONFIG_TARGET_MB_WORD_SWAP ; 
 int /*<<< orphan*/  BNX2_PCI_CONFIG_3 ; 
 int BNX2_PCI_CONFIG_3_VAUX_PRESET ; 
 int BNX2_PHY_FLAG_2_5G_CAPABLE ; 
 int BNX2_PHY_FLAG_CRC_FIX ; 
 int BNX2_PHY_FLAG_DIS_EARLY_DAC ; 
 int BNX2_PHY_FLAG_NO_PARALLEL ; 
 int BNX2_PHY_FLAG_SERDES ; 
 int /*<<< orphan*/  BNX2_PORT_FEATURE ; 
 int BNX2_PORT_FEATURE_ASF_ENABLED ; 
 int BNX2_PORT_FEATURE_WOL_ENABLED ; 
 int /*<<< orphan*/  BNX2_PORT_HW_CFG_MAC_LOWER ; 
 int /*<<< orphan*/  BNX2_PORT_HW_CFG_MAC_UPPER ; 
 int BNX2_RD (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2_SHARED_HW_CFG_CONFIG ; 
 int BNX2_SHARED_HW_CFG_GIG_LINK_ON_VAUX ; 
 int BNX2_SHARED_HW_CFG_PHY_2_5G ; 
 int BNX2_SHM_HDR_ADDR_0 ; 
 int BNX2_SHM_HDR_SIGNATURE ; 
 int BNX2_SHM_HDR_SIGNATURE_SIG ; 
 int BNX2_SHM_HDR_SIGNATURE_SIG_MASK ; 
 int /*<<< orphan*/  BNX2_TIMER_INTERVAL ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRV_MODULE_NAME ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int FLOW_CTRL_RX ; 
 int FLOW_CTRL_TX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HOST_VIEW_SHMEM_BASE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  MB_GET_CID_ADDR (scalar_t__) ; 
 int /*<<< orphan*/  NETIF_F_HIGHDMA ; 
 int /*<<< orphan*/  PCI_CAP_ID_PCIX ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_PARITY ; 
 int PCI_COMMAND_SERR ; 
 int /*<<< orphan*/  PCI_DEVICE_ID_AMD_8132_BRIDGE ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_AMD ; 
 scalar_t__ PCI_VENDOR_ID_HP ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_TP ; 
 int /*<<< orphan*/  RUN_AT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ TX_MAX_TSS_RINGS ; 
 scalar_t__ TX_TSS_CID ; 
 int USEC_PER_SEC ; 
 int be32_to_cpu (int) ; 
 int bnx2_alloc_stats_blk (struct net_device*) ; 
 int /*<<< orphan*/  bnx2_cnic_probe ; 
 int /*<<< orphan*/  bnx2_get_5709_media (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_get_pci_speed (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_init_fw_cap (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_init_nvram (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_read_vpd_fw_ver (struct bnx2*) ; 
 int bnx2_reg_rd_ind (struct bnx2*,int) ; 
 int /*<<< orphan*/  bnx2_reset_task ; 
 int /*<<< orphan*/  bnx2_set_default_link (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_set_rx_ring_size (struct bnx2*,int) ; 
 int bnx2_shmem_rd (struct bnx2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2_timer ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 int disable_msi ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int pci_enable_pcie_error_reporting (struct pci_dev*) ; 
 scalar_t__ pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/ * pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_resource_flags (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int pci_set_consistent_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_set_dma_mask (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  timer_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnx2_init_board(struct pci_dev *pdev, struct net_device *dev)
{
	struct bnx2 *bp;
	int rc, i, j;
	u32 reg;
	u64 dma_mask, persist_dma_mask;
	int err;

	SET_NETDEV_DEV(dev, &pdev->dev);
	bp = netdev_priv(dev);

	bp->flags = 0;
	bp->phy_flags = 0;

	bp->temp_stats_blk =
		kzalloc(sizeof(struct statistics_block), GFP_KERNEL);

	if (!bp->temp_stats_blk) {
		rc = -ENOMEM;
		goto err_out;
	}

	/* enable device (incl. PCI PM wakeup), and bus-mastering */
	rc = pci_enable_device(pdev);
	if (rc) {
		dev_err(&pdev->dev, "Cannot enable PCI device, aborting\n");
		goto err_out;
	}

	if (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) {
		dev_err(&pdev->dev,
			"Cannot find PCI device base address, aborting\n");
		rc = -ENODEV;
		goto err_out_disable;
	}

	rc = pci_request_regions(pdev, DRV_MODULE_NAME);
	if (rc) {
		dev_err(&pdev->dev, "Cannot obtain PCI resources, aborting\n");
		goto err_out_disable;
	}

	pci_set_master(pdev);

	bp->pm_cap = pdev->pm_cap;
	if (bp->pm_cap == 0) {
		dev_err(&pdev->dev,
			"Cannot find power management capability, aborting\n");
		rc = -EIO;
		goto err_out_release;
	}

	bp->dev = dev;
	bp->pdev = pdev;

	spin_lock_init(&bp->phy_lock);
	spin_lock_init(&bp->indirect_lock);
#ifdef BCM_CNIC
	mutex_init(&bp->cnic_lock);
#endif
	INIT_WORK(&bp->reset_task, bnx2_reset_task);

	bp->regview = pci_iomap(pdev, 0, MB_GET_CID_ADDR(TX_TSS_CID +
							 TX_MAX_TSS_RINGS + 1));
	if (!bp->regview) {
		dev_err(&pdev->dev, "Cannot map register space, aborting\n");
		rc = -ENOMEM;
		goto err_out_release;
	}

	/* Configure byte swap and enable write to the reg_window registers.
	 * Rely on CPU to do target byte swapping on big endian systems
	 * The chip's target access swapping will not swap all accesses
	 */
	BNX2_WR(bp, BNX2_PCICFG_MISC_CONFIG,
		BNX2_PCICFG_MISC_CONFIG_REG_WINDOW_ENA |
		BNX2_PCICFG_MISC_CONFIG_TARGET_MB_WORD_SWAP);

	bp->chip_id = BNX2_RD(bp, BNX2_MISC_ID);

	if (BNX2_CHIP(bp) == BNX2_CHIP_5709) {
		if (!pci_is_pcie(pdev)) {
			dev_err(&pdev->dev, "Not PCIE, aborting\n");
			rc = -EIO;
			goto err_out_unmap;
		}
		bp->flags |= BNX2_FLAG_PCIE;
		if (BNX2_CHIP_REV(bp) == BNX2_CHIP_REV_Ax)
			bp->flags |= BNX2_FLAG_JUMBO_BROKEN;

		/* AER (Advanced Error Reporting) hooks */
		err = pci_enable_pcie_error_reporting(pdev);
		if (!err)
			bp->flags |= BNX2_FLAG_AER_ENABLED;

	} else {
		bp->pcix_cap = pci_find_capability(pdev, PCI_CAP_ID_PCIX);
		if (bp->pcix_cap == 0) {
			dev_err(&pdev->dev,
				"Cannot find PCIX capability, aborting\n");
			rc = -EIO;
			goto err_out_unmap;
		}
		bp->flags |= BNX2_FLAG_BROKEN_STATS;
	}

	if (BNX2_CHIP(bp) == BNX2_CHIP_5709 &&
	    BNX2_CHIP_REV(bp) != BNX2_CHIP_REV_Ax) {
		if (pdev->msix_cap)
			bp->flags |= BNX2_FLAG_MSIX_CAP;
	}

	if (BNX2_CHIP_ID(bp) != BNX2_CHIP_ID_5706_A0 &&
	    BNX2_CHIP_ID(bp) != BNX2_CHIP_ID_5706_A1) {
		if (pdev->msi_cap)
			bp->flags |= BNX2_FLAG_MSI_CAP;
	}

	/* 5708 cannot support DMA addresses > 40-bit.  */
	if (BNX2_CHIP(bp) == BNX2_CHIP_5708)
		persist_dma_mask = dma_mask = DMA_BIT_MASK(40);
	else
		persist_dma_mask = dma_mask = DMA_BIT_MASK(64);

	/* Configure DMA attributes. */
	if (pci_set_dma_mask(pdev, dma_mask) == 0) {
		dev->features |= NETIF_F_HIGHDMA;
		rc = pci_set_consistent_dma_mask(pdev, persist_dma_mask);
		if (rc) {
			dev_err(&pdev->dev,
				"pci_set_consistent_dma_mask failed, aborting\n");
			goto err_out_unmap;
		}
	} else if ((rc = pci_set_dma_mask(pdev, DMA_BIT_MASK(32))) != 0) {
		dev_err(&pdev->dev, "System does not support DMA, aborting\n");
		goto err_out_unmap;
	}

	if (!(bp->flags & BNX2_FLAG_PCIE))
		bnx2_get_pci_speed(bp);

	/* 5706A0 may falsely detect SERR and PERR. */
	if (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A0) {
		reg = BNX2_RD(bp, PCI_COMMAND);
		reg &= ~(PCI_COMMAND_SERR | PCI_COMMAND_PARITY);
		BNX2_WR(bp, PCI_COMMAND, reg);
	} else if ((BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A1) &&
		!(bp->flags & BNX2_FLAG_PCIX)) {

		dev_err(&pdev->dev,
			"5706 A1 can only be used in a PCIX bus, aborting\n");
		goto err_out_unmap;
	}

	bnx2_init_nvram(bp);

	reg = bnx2_reg_rd_ind(bp, BNX2_SHM_HDR_SIGNATURE);

	if (bnx2_reg_rd_ind(bp, BNX2_MCP_TOE_ID) & BNX2_MCP_TOE_ID_FUNCTION_ID)
		bp->func = 1;

	if ((reg & BNX2_SHM_HDR_SIGNATURE_SIG_MASK) ==
	    BNX2_SHM_HDR_SIGNATURE_SIG) {
		u32 off = bp->func << 2;

		bp->shmem_base = bnx2_reg_rd_ind(bp, BNX2_SHM_HDR_ADDR_0 + off);
	} else
		bp->shmem_base = HOST_VIEW_SHMEM_BASE;

	/* Get the permanent MAC address.  First we need to make sure the
	 * firmware is actually running.
	 */
	reg = bnx2_shmem_rd(bp, BNX2_DEV_INFO_SIGNATURE);

	if ((reg & BNX2_DEV_INFO_SIGNATURE_MAGIC_MASK) !=
	    BNX2_DEV_INFO_SIGNATURE_MAGIC) {
		dev_err(&pdev->dev, "Firmware not running, aborting\n");
		rc = -ENODEV;
		goto err_out_unmap;
	}

	bnx2_read_vpd_fw_ver(bp);

	j = strlen(bp->fw_version);
	reg = bnx2_shmem_rd(bp, BNX2_DEV_INFO_BC_REV);
	for (i = 0; i < 3 && j < 24; i++) {
		u8 num, k, skip0;

		if (i == 0) {
			bp->fw_version[j++] = 'b';
			bp->fw_version[j++] = 'c';
			bp->fw_version[j++] = ' ';
		}
		num = (u8) (reg >> (24 - (i * 8)));
		for (k = 100, skip0 = 1; k >= 1; num %= k, k /= 10) {
			if (num >= k || !skip0 || k == 1) {
				bp->fw_version[j++] = (num / k) + '0';
				skip0 = 0;
			}
		}
		if (i != 2)
			bp->fw_version[j++] = '.';
	}
	reg = bnx2_shmem_rd(bp, BNX2_PORT_FEATURE);
	if (reg & BNX2_PORT_FEATURE_WOL_ENABLED)
		bp->wol = 1;

	if (reg & BNX2_PORT_FEATURE_ASF_ENABLED) {
		bp->flags |= BNX2_FLAG_ASF_ENABLE;

		for (i = 0; i < 30; i++) {
			reg = bnx2_shmem_rd(bp, BNX2_BC_STATE_CONDITION);
			if (reg & BNX2_CONDITION_MFW_RUN_MASK)
				break;
			msleep(10);
		}
	}
	reg = bnx2_shmem_rd(bp, BNX2_BC_STATE_CONDITION);
	reg &= BNX2_CONDITION_MFW_RUN_MASK;
	if (reg != BNX2_CONDITION_MFW_RUN_UNKNOWN &&
	    reg != BNX2_CONDITION_MFW_RUN_NONE) {
		u32 addr = bnx2_shmem_rd(bp, BNX2_MFW_VER_PTR);

		if (j < 32)
			bp->fw_version[j++] = ' ';
		for (i = 0; i < 3 && j < 28; i++) {
			reg = bnx2_reg_rd_ind(bp, addr + i * 4);
			reg = be32_to_cpu(reg);
			memcpy(&bp->fw_version[j], &reg, 4);
			j += 4;
		}
	}

	reg = bnx2_shmem_rd(bp, BNX2_PORT_HW_CFG_MAC_UPPER);
	bp->mac_addr[0] = (u8) (reg >> 8);
	bp->mac_addr[1] = (u8) reg;

	reg = bnx2_shmem_rd(bp, BNX2_PORT_HW_CFG_MAC_LOWER);
	bp->mac_addr[2] = (u8) (reg >> 24);
	bp->mac_addr[3] = (u8) (reg >> 16);
	bp->mac_addr[4] = (u8) (reg >> 8);
	bp->mac_addr[5] = (u8) reg;

	bp->tx_ring_size = BNX2_MAX_TX_DESC_CNT;
	bnx2_set_rx_ring_size(bp, 255);

	bp->tx_quick_cons_trip_int = 2;
	bp->tx_quick_cons_trip = 20;
	bp->tx_ticks_int = 18;
	bp->tx_ticks = 80;

	bp->rx_quick_cons_trip_int = 2;
	bp->rx_quick_cons_trip = 12;
	bp->rx_ticks_int = 18;
	bp->rx_ticks = 18;

	bp->stats_ticks = USEC_PER_SEC & BNX2_HC_STATS_TICKS_HC_STAT_TICKS;

	bp->current_interval = BNX2_TIMER_INTERVAL;

	bp->phy_addr = 1;

	/* allocate stats_blk */
	rc = bnx2_alloc_stats_blk(dev);
	if (rc)
		goto err_out_unmap;

	/* Disable WOL support if we are running on a SERDES chip. */
	if (BNX2_CHIP(bp) == BNX2_CHIP_5709)
		bnx2_get_5709_media(bp);
	else if (BNX2_CHIP_BOND(bp) & BNX2_CHIP_BOND_SERDES_BIT)
		bp->phy_flags |= BNX2_PHY_FLAG_SERDES;

	bp->phy_port = PORT_TP;
	if (bp->phy_flags & BNX2_PHY_FLAG_SERDES) {
		bp->phy_port = PORT_FIBRE;
		reg = bnx2_shmem_rd(bp, BNX2_SHARED_HW_CFG_CONFIG);
		if (!(reg & BNX2_SHARED_HW_CFG_GIG_LINK_ON_VAUX)) {
			bp->flags |= BNX2_FLAG_NO_WOL;
			bp->wol = 0;
		}
		if (BNX2_CHIP(bp) == BNX2_CHIP_5706) {
			/* Don't do parallel detect on this board because of
			 * some board problems.  The link will not go down
			 * if we do parallel detect.
			 */
			if (pdev->subsystem_vendor == PCI_VENDOR_ID_HP &&
			    pdev->subsystem_device == 0x310c)
				bp->phy_flags |= BNX2_PHY_FLAG_NO_PARALLEL;
		} else {
			bp->phy_addr = 2;
			if (reg & BNX2_SHARED_HW_CFG_PHY_2_5G)
				bp->phy_flags |= BNX2_PHY_FLAG_2_5G_CAPABLE;
		}
	} else if (BNX2_CHIP(bp) == BNX2_CHIP_5706 ||
		   BNX2_CHIP(bp) == BNX2_CHIP_5708)
		bp->phy_flags |= BNX2_PHY_FLAG_CRC_FIX;
	else if (BNX2_CHIP(bp) == BNX2_CHIP_5709 &&
		 (BNX2_CHIP_REV(bp) == BNX2_CHIP_REV_Ax ||
		  BNX2_CHIP_REV(bp) == BNX2_CHIP_REV_Bx))
		bp->phy_flags |= BNX2_PHY_FLAG_DIS_EARLY_DAC;

	bnx2_init_fw_cap(bp);

	if ((BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5708_A0) ||
	    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5708_B0) ||
	    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5708_B1) ||
	    !(BNX2_RD(bp, BNX2_PCI_CONFIG_3) & BNX2_PCI_CONFIG_3_VAUX_PRESET)) {
		bp->flags |= BNX2_FLAG_NO_WOL;
		bp->wol = 0;
	}

	if (bp->flags & BNX2_FLAG_NO_WOL)
		device_set_wakeup_capable(&bp->pdev->dev, false);
	else
		device_set_wakeup_enable(&bp->pdev->dev, bp->wol);

	if (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5706_A0) {
		bp->tx_quick_cons_trip_int =
			bp->tx_quick_cons_trip;
		bp->tx_ticks_int = bp->tx_ticks;
		bp->rx_quick_cons_trip_int =
			bp->rx_quick_cons_trip;
		bp->rx_ticks_int = bp->rx_ticks;
		bp->comp_prod_trip_int = bp->comp_prod_trip;
		bp->com_ticks_int = bp->com_ticks;
		bp->cmd_ticks_int = bp->cmd_ticks;
	}

	/* Disable MSI on 5706 if AMD 8132 bridge is found.
	 *
	 * MSI is defined to be 32-bit write.  The 5706 does 64-bit MSI writes
	 * with byte enables disabled on the unused 32-bit word.  This is legal
	 * but causes problems on the AMD 8132 which will eventually stop
	 * responding after a while.
	 *
	 * AMD believes this incompatibility is unique to the 5706, and
	 * prefers to locally disable MSI rather than globally disabling it.
	 */
	if (BNX2_CHIP(bp) == BNX2_CHIP_5706 && disable_msi == 0) {
		struct pci_dev *amd_8132 = NULL;

		while ((amd_8132 = pci_get_device(PCI_VENDOR_ID_AMD,
						  PCI_DEVICE_ID_AMD_8132_BRIDGE,
						  amd_8132))) {

			if (amd_8132->revision >= 0x10 &&
			    amd_8132->revision <= 0x13) {
				disable_msi = 1;
				pci_dev_put(amd_8132);
				break;
			}
		}
	}

	bnx2_set_default_link(bp);
	bp->req_flow_ctrl = FLOW_CTRL_RX | FLOW_CTRL_TX;

	timer_setup(&bp->timer, bnx2_timer, 0);
	bp->timer.expires = RUN_AT(BNX2_TIMER_INTERVAL);

#ifdef BCM_CNIC
	if (bnx2_shmem_rd(bp, BNX2_ISCSI_INITIATOR) & BNX2_ISCSI_INITIATOR_EN)
		bp->cnic_eth_dev.max_iscsi_conn =
			(bnx2_shmem_rd(bp, BNX2_ISCSI_MAX_CONN) &
			 BNX2_ISCSI_MAX_CONN_MASK) >> BNX2_ISCSI_MAX_CONN_SHIFT;
	bp->cnic_probe = bnx2_cnic_probe;
#endif
	pci_save_state(pdev);

	return 0;

err_out_unmap:
	if (bp->flags & BNX2_FLAG_AER_ENABLED) {
		pci_disable_pcie_error_reporting(pdev);
		bp->flags &= ~BNX2_FLAG_AER_ENABLED;
	}

	pci_iounmap(pdev, bp->regview);
	bp->regview = NULL;

err_out_release:
	pci_release_regions(pdev);

err_out_disable:
	pci_disable_device(pdev);

err_out:
	kfree(bp->temp_stats_blk);

	return rc;
}