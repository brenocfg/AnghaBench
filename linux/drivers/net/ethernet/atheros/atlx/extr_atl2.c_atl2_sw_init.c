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
struct pci_dev {int /*<<< orphan*/  revision; int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct atl2_hw {int phy_configured; int preamble_len; int ipgt; int min_ifg; int ipgr1; int ipgr2; int retry_buf; int max_retry; int lcol; int jam_ipg; int /*<<< orphan*/  max_frame_size; scalar_t__ fc_rxd_lo; scalar_t__ fc_rxd_hi; int /*<<< orphan*/  pci_cmd_word; int /*<<< orphan*/  revision_id; int /*<<< orphan*/  subsystem_id; int /*<<< orphan*/  subsystem_vendor_id; int /*<<< orphan*/  device_id; int /*<<< orphan*/  vendor_id; } ;
struct atl2_adapter {int ict; int /*<<< orphan*/  flags; int /*<<< orphan*/  stats_lock; TYPE_1__* netdev; int /*<<< orphan*/  link_duplex; int /*<<< orphan*/  link_speed; scalar_t__ wol; struct pci_dev* pdev; struct atl2_hw hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  FULL_DUPLEX ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int /*<<< orphan*/  SPEED_0 ; 
 int /*<<< orphan*/  __ATL2_DOWN ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atl2_sw_init(struct atl2_adapter *adapter)
{
	struct atl2_hw *hw = &adapter->hw;
	struct pci_dev *pdev = adapter->pdev;

	/* PCI config space info */
	hw->vendor_id = pdev->vendor;
	hw->device_id = pdev->device;
	hw->subsystem_vendor_id = pdev->subsystem_vendor;
	hw->subsystem_id = pdev->subsystem_device;
	hw->revision_id  = pdev->revision;

	pci_read_config_word(pdev, PCI_COMMAND, &hw->pci_cmd_word);

	adapter->wol = 0;
	adapter->ict = 50000;  /* ~100ms */
	adapter->link_speed = SPEED_0;   /* hardware init */
	adapter->link_duplex = FULL_DUPLEX;

	hw->phy_configured = false;
	hw->preamble_len = 7;
	hw->ipgt = 0x60;
	hw->min_ifg = 0x50;
	hw->ipgr1 = 0x40;
	hw->ipgr2 = 0x60;
	hw->retry_buf = 2;
	hw->max_retry = 0xf;
	hw->lcol = 0x37;
	hw->jam_ipg = 7;
	hw->fc_rxd_hi = 0;
	hw->fc_rxd_lo = 0;
	hw->max_frame_size = adapter->netdev->mtu;

	spin_lock_init(&adapter->stats_lock);

	set_bit(__ATL2_DOWN, &adapter->flags);

	return 0;
}