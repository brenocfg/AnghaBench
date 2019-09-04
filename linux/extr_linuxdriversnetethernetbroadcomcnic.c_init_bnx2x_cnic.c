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
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct cnic_local {int /*<<< orphan*/  close_conn; int /*<<< orphan*/  arm_int; int /*<<< orphan*/  ack_int; int /*<<< orphan*/  disable_int_sync; int /*<<< orphan*/  enable_int; int /*<<< orphan*/  stop_cm; int /*<<< orphan*/  start_cm; int /*<<< orphan*/  free_resc; int /*<<< orphan*/  alloc_resc; int /*<<< orphan*/  setup_pgtbl; int /*<<< orphan*/  stop_hw; int /*<<< orphan*/  start_hw; int /*<<< orphan*/ * cnic_ops; int /*<<< orphan*/  chip_id; struct cnic_eth_dev* ethdev; } ;
struct cnic_eth_dev {int drv_state; scalar_t__ max_fcoe_conn; int /*<<< orphan*/  iscsi_mac; int /*<<< orphan*/  max_fcoe_exchanges; int /*<<< orphan*/  max_iscsi_conn; int /*<<< orphan*/  addr_drv_info_to_mcp; int /*<<< orphan*/  chip_id; struct pci_dev* pdev; } ;
struct cnic_dev {scalar_t__ max_fcoe_conn; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  max_fcoe_exchanges; int /*<<< orphan*/  max_iscsi_conn; int /*<<< orphan*/  stats_addr; struct pci_dev* pcidev; struct cnic_local* cnic_priv; int /*<<< orphan*/  submit_kwqes; int /*<<< orphan*/  flags; } ;
struct bnx2x {struct cnic_eth_dev* (* cnic_probe ) (struct net_device*) ;} ;

/* Variables and functions */
 scalar_t__ BNX2X_CHIP_IS_E2_PLUS (struct bnx2x*) ; 
 scalar_t__ BNX2X_FCOE_NUM_CONNECTIONS ; 
 int CNIC_DRV_STATE_NO_ISCSI ; 
 int /*<<< orphan*/  CNIC_F_BNX2X_CLASS ; 
 scalar_t__ CNIC_SUPPORTS_FCOE (struct bnx2x*) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  cnic_ack_bnx2x_e2_msix ; 
 int /*<<< orphan*/  cnic_ack_bnx2x_msix ; 
 int /*<<< orphan*/  cnic_alloc_bnx2x_resc ; 
 struct cnic_dev* cnic_alloc_dev (struct net_device*,struct pci_dev*) ; 
 int /*<<< orphan*/  cnic_arm_bnx2x_e2_msix ; 
 int /*<<< orphan*/  cnic_arm_bnx2x_msix ; 
 int /*<<< orphan*/  cnic_bnx2x_ops ; 
 int /*<<< orphan*/  cnic_close_bnx2x_conn ; 
 int /*<<< orphan*/  cnic_cm_init_bnx2x_hw ; 
 int /*<<< orphan*/  cnic_cm_stop_bnx2x_hw ; 
 int /*<<< orphan*/  cnic_disable_bnx2x_int_sync ; 
 int /*<<< orphan*/  cnic_enable_bnx2x_int ; 
 int /*<<< orphan*/  cnic_free_resc ; 
 int /*<<< orphan*/  cnic_setup_page_tbl_le ; 
 int /*<<< orphan*/  cnic_start_bnx2x_hw ; 
 int /*<<< orphan*/  cnic_stop_bnx2x_hw ; 
 int /*<<< orphan*/  cnic_submit_bnx2x_kwqes ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cnic_eth_dev* stub1 (struct net_device*) ; 

__attribute__((used)) static struct cnic_dev *init_bnx2x_cnic(struct net_device *dev)
{
	struct pci_dev *pdev;
	struct cnic_dev *cdev;
	struct cnic_local *cp;
	struct bnx2x *bp = netdev_priv(dev);
	struct cnic_eth_dev *ethdev = NULL;

	if (bp->cnic_probe)
		ethdev = bp->cnic_probe(dev);

	if (!ethdev)
		return NULL;

	pdev = ethdev->pdev;
	if (!pdev)
		return NULL;

	dev_hold(dev);
	cdev = cnic_alloc_dev(dev, pdev);
	if (cdev == NULL) {
		dev_put(dev);
		return NULL;
	}

	set_bit(CNIC_F_BNX2X_CLASS, &cdev->flags);
	cdev->submit_kwqes = cnic_submit_bnx2x_kwqes;

	cp = cdev->cnic_priv;
	cp->ethdev = ethdev;
	cdev->pcidev = pdev;
	cp->chip_id = ethdev->chip_id;

	cdev->stats_addr = ethdev->addr_drv_info_to_mcp;

	if (!(ethdev->drv_state & CNIC_DRV_STATE_NO_ISCSI))
		cdev->max_iscsi_conn = ethdev->max_iscsi_conn;
	if (CNIC_SUPPORTS_FCOE(bp)) {
		cdev->max_fcoe_conn = ethdev->max_fcoe_conn;
		cdev->max_fcoe_exchanges = ethdev->max_fcoe_exchanges;
	}

	if (cdev->max_fcoe_conn > BNX2X_FCOE_NUM_CONNECTIONS)
		cdev->max_fcoe_conn = BNX2X_FCOE_NUM_CONNECTIONS;

	memcpy(cdev->mac_addr, ethdev->iscsi_mac, ETH_ALEN);

	cp->cnic_ops = &cnic_bnx2x_ops;
	cp->start_hw = cnic_start_bnx2x_hw;
	cp->stop_hw = cnic_stop_bnx2x_hw;
	cp->setup_pgtbl = cnic_setup_page_tbl_le;
	cp->alloc_resc = cnic_alloc_bnx2x_resc;
	cp->free_resc = cnic_free_resc;
	cp->start_cm = cnic_cm_init_bnx2x_hw;
	cp->stop_cm = cnic_cm_stop_bnx2x_hw;
	cp->enable_int = cnic_enable_bnx2x_int;
	cp->disable_int_sync = cnic_disable_bnx2x_int_sync;
	if (BNX2X_CHIP_IS_E2_PLUS(bp)) {
		cp->ack_int = cnic_ack_bnx2x_e2_msix;
		cp->arm_int = cnic_arm_bnx2x_e2_msix;
	} else {
		cp->ack_int = cnic_ack_bnx2x_msix;
		cp->arm_int = cnic_arm_bnx2x_msix;
	}
	cp->close_conn = cnic_close_bnx2x_conn;
	return cdev;
}