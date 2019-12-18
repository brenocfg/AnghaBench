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
typedef  int u32 ;
struct pci_dev {int revision; int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct atl1e_hw {int revision_id; int emi_ca; int phy_configured; int preamble_len; int max_frame_size; int rx_jumbo_th; int ict; int smb_timer; int tpd_burst; int rrd_thresh; int tpd_thresh; int rx_count_down; int tx_count_down; int imt; int dmar_dly_cnt; int dmaw_dly_cnt; void* dmaw_block; void* dmar_block; scalar_t__ base_cpu; scalar_t__ indirect_tab; int /*<<< orphan*/  rrs_type; int /*<<< orphan*/  nic_type; int /*<<< orphan*/  pci_cmd_word; int /*<<< orphan*/  subsystem_id; int /*<<< orphan*/  subsystem_vendor_id; int /*<<< orphan*/  device_id; int /*<<< orphan*/  vendor_id; } ;
struct TYPE_3__ {int count; } ;
struct atl1e_adapter {int num_rx_queues; int /*<<< orphan*/  flags; int /*<<< orphan*/  mdio_lock; int /*<<< orphan*/  irq_sem; TYPE_2__* netdev; TYPE_1__ tx_ring; int /*<<< orphan*/  link_duplex; int /*<<< orphan*/  link_speed; scalar_t__ wol; struct pci_dev* pdev; struct atl1e_hw hw; } ;
struct TYPE_4__ {int mtu; } ;

/* Variables and functions */
 int AT_READ_REG (struct atl1e_hw*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  FULL_DUPLEX ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PHY_STATUS_100M ; 
 int PHY_STATUS_EMI_CA ; 
 int /*<<< orphan*/  REG_PHY_STATUS ; 
 int /*<<< orphan*/  SPEED_0 ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  __AT_DOWN ; 
 int /*<<< orphan*/  athr_l1e ; 
 int /*<<< orphan*/  athr_l2e_revA ; 
 int /*<<< orphan*/  athr_l2e_revB ; 
 scalar_t__ atl1e_alloc_queues (struct atl1e_adapter*) ; 
 void* atl1e_dma_req_1024 ; 
 int /*<<< orphan*/  atl1e_rrs_disable ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atl1e_sw_init(struct atl1e_adapter *adapter)
{
	struct atl1e_hw *hw   = &adapter->hw;
	struct pci_dev	*pdev = adapter->pdev;
	u32 phy_status_data = 0;

	adapter->wol = 0;
	adapter->link_speed = SPEED_0;   /* hardware init */
	adapter->link_duplex = FULL_DUPLEX;
	adapter->num_rx_queues = 1;

	/* PCI config space info */
	hw->vendor_id = pdev->vendor;
	hw->device_id = pdev->device;
	hw->subsystem_vendor_id = pdev->subsystem_vendor;
	hw->subsystem_id = pdev->subsystem_device;
	hw->revision_id  = pdev->revision;

	pci_read_config_word(pdev, PCI_COMMAND, &hw->pci_cmd_word);

	phy_status_data = AT_READ_REG(hw, REG_PHY_STATUS);
	/* nic type */
	if (hw->revision_id >= 0xF0) {
		hw->nic_type = athr_l2e_revB;
	} else {
		if (phy_status_data & PHY_STATUS_100M)
			hw->nic_type = athr_l1e;
		else
			hw->nic_type = athr_l2e_revA;
	}

	phy_status_data = AT_READ_REG(hw, REG_PHY_STATUS);

	if (phy_status_data & PHY_STATUS_EMI_CA)
		hw->emi_ca = true;
	else
		hw->emi_ca = false;

	hw->phy_configured = false;
	hw->preamble_len = 7;
	hw->max_frame_size = adapter->netdev->mtu;
	hw->rx_jumbo_th = (hw->max_frame_size + ETH_HLEN +
				VLAN_HLEN + ETH_FCS_LEN + 7) >> 3;

	hw->rrs_type = atl1e_rrs_disable;
	hw->indirect_tab = 0;
	hw->base_cpu = 0;

	/* need confirm */

	hw->ict = 50000;                 /* 100ms */
	hw->smb_timer = 200000;          /* 200ms  */
	hw->tpd_burst = 5;
	hw->rrd_thresh = 1;
	hw->tpd_thresh = adapter->tx_ring.count / 2;
	hw->rx_count_down = 4;  /* 2us resolution */
	hw->tx_count_down = hw->imt * 4 / 3;
	hw->dmar_block = atl1e_dma_req_1024;
	hw->dmaw_block = atl1e_dma_req_1024;
	hw->dmar_dly_cnt = 15;
	hw->dmaw_dly_cnt = 4;

	if (atl1e_alloc_queues(adapter)) {
		netdev_err(adapter->netdev, "Unable to allocate memory for queues\n");
		return -ENOMEM;
	}

	atomic_set(&adapter->irq_sem, 1);
	spin_lock_init(&adapter->mdio_lock);

	set_bit(__AT_DOWN, &adapter->flags);

	return 0;
}