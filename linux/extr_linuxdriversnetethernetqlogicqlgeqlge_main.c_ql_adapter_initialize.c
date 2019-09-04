#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ql_adapter {int rx_ring_count; int rss_ring_count; int tx_ring_count; TYPE_3__* rx_ring; TYPE_4__* ndev; TYPE_2__* nic_ops; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/  wol; TYPE_1__* pdev; } ;
struct TYPE_8__ {int features; } ;
struct TYPE_7__ {int /*<<< orphan*/  napi; } ;
struct TYPE_6__ {int (* port_initialize ) (struct ql_adapter*) ;} ;
struct TYPE_5__ {int subsystem_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSC ; 
 int FSC_DBL_MASK ; 
 int FSC_DBRST_MASK ; 
 int FSC_EC ; 
 int FSC_EPC_INBOUND ; 
 int FSC_EPC_OUTBOUND ; 
 int FSC_FE ; 
 int FSC_VM_PAGESIZE_MASK ; 
 int FSC_VM_PAGE_4K ; 
 int /*<<< orphan*/  INTR_MASK ; 
 int INTR_MASK_PI ; 
 int /*<<< orphan*/  MGMT_RCV_CFG ; 
 int MGMT_RCV_CFG_RM ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int /*<<< orphan*/  NIC_RCV_CFG ; 
 int NIC_RCV_CFG_DFQ ; 
 int NIC_RCV_CFG_DFQ_MASK ; 
 int NIC_RCV_CFG_RV ; 
 int /*<<< orphan*/  RST_FO ; 
 int RST_FO_RR_MASK ; 
 int RST_FO_RR_RCV_FUNC_CQ ; 
 int /*<<< orphan*/  SPLT_HDR ; 
 int SPLT_LEN ; 
 int SPLT_SETTING ; 
 int /*<<< orphan*/  SYS ; 
 int SYS_EFE ; 
 int SYS_FAE ; 
 int /*<<< orphan*/  WAKE_MAGIC ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,TYPE_4__*,char*,...) ; 
 int ql_cam_route_initialize (struct ql_adapter*) ; 
 int ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int ql_start_rss (struct ql_adapter*) ; 
 int ql_start_rx_ring (struct ql_adapter*,TYPE_3__*) ; 
 int ql_start_tx_ring (struct ql_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct ql_adapter*) ; 

__attribute__((used)) static int ql_adapter_initialize(struct ql_adapter *qdev)
{
	u32 value, mask;
	int i;
	int status = 0;

	/*
	 * Set up the System register to halt on errors.
	 */
	value = SYS_EFE | SYS_FAE;
	mask = value << 16;
	ql_write32(qdev, SYS, mask | value);

	/* Set the default queue, and VLAN behavior. */
	value = NIC_RCV_CFG_DFQ;
	mask = NIC_RCV_CFG_DFQ_MASK;
	if (qdev->ndev->features & NETIF_F_HW_VLAN_CTAG_RX) {
		value |= NIC_RCV_CFG_RV;
		mask |= (NIC_RCV_CFG_RV << 16);
	}
	ql_write32(qdev, NIC_RCV_CFG, (mask | value));

	/* Set the MPI interrupt to enabled. */
	ql_write32(qdev, INTR_MASK, (INTR_MASK_PI << 16) | INTR_MASK_PI);

	/* Enable the function, set pagesize, enable error checking. */
	value = FSC_FE | FSC_EPC_INBOUND | FSC_EPC_OUTBOUND |
	    FSC_EC | FSC_VM_PAGE_4K;
	value |= SPLT_SETTING;

	/* Set/clear header splitting. */
	mask = FSC_VM_PAGESIZE_MASK |
	    FSC_DBL_MASK | FSC_DBRST_MASK | (value << 16);
	ql_write32(qdev, FSC, mask | value);

	ql_write32(qdev, SPLT_HDR, SPLT_LEN);

	/* Set RX packet routing to use port/pci function on which the
	 * packet arrived on in addition to usual frame routing.
	 * This is helpful on bonding where both interfaces can have
	 * the same MAC address.
	 */
	ql_write32(qdev, RST_FO, RST_FO_RR_MASK | RST_FO_RR_RCV_FUNC_CQ);
	/* Reroute all packets to our Interface.
	 * They may have been routed to MPI firmware
	 * due to WOL.
	 */
	value = ql_read32(qdev, MGMT_RCV_CFG);
	value &= ~MGMT_RCV_CFG_RM;
	mask = 0xffff0000;

	/* Sticky reg needs clearing due to WOL. */
	ql_write32(qdev, MGMT_RCV_CFG, mask);
	ql_write32(qdev, MGMT_RCV_CFG, mask | value);

	/* Default WOL is enable on Mezz cards */
	if (qdev->pdev->subsystem_device == 0x0068 ||
			qdev->pdev->subsystem_device == 0x0180)
		qdev->wol = WAKE_MAGIC;

	/* Start up the rx queues. */
	for (i = 0; i < qdev->rx_ring_count; i++) {
		status = ql_start_rx_ring(qdev, &qdev->rx_ring[i]);
		if (status) {
			netif_err(qdev, ifup, qdev->ndev,
				  "Failed to start rx ring[%d].\n", i);
			return status;
		}
	}

	/* If there is more than one inbound completion queue
	 * then download a RICB to configure RSS.
	 */
	if (qdev->rss_ring_count > 1) {
		status = ql_start_rss(qdev);
		if (status) {
			netif_err(qdev, ifup, qdev->ndev, "Failed to start RSS.\n");
			return status;
		}
	}

	/* Start up the tx queues. */
	for (i = 0; i < qdev->tx_ring_count; i++) {
		status = ql_start_tx_ring(qdev, &qdev->tx_ring[i]);
		if (status) {
			netif_err(qdev, ifup, qdev->ndev,
				  "Failed to start tx ring[%d].\n", i);
			return status;
		}
	}

	/* Initialize the port and set the max framesize. */
	status = qdev->nic_ops->port_initialize(qdev);
	if (status)
		netif_err(qdev, ifup, qdev->ndev, "Failed to start port.\n");

	/* Set up the MAC address and frame routing filter. */
	status = ql_cam_route_initialize(qdev);
	if (status) {
		netif_err(qdev, ifup, qdev->ndev,
			  "Failed to init CAM/Routing tables.\n");
		return status;
	}

	/* Start NAPI for the RSS queues. */
	for (i = 0; i < qdev->rss_ring_count; i++)
		napi_enable(&qdev->rx_ring[i].napi);

	return status;
}