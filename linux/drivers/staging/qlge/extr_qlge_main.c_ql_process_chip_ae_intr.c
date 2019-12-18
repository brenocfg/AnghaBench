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
struct ql_adapter {int /*<<< orphan*/  ndev; } ;
struct ib_ae_iocb_rsp {int event; int /*<<< orphan*/  q_id; } ;

/* Variables and functions */
#define  CAM_LOOKUP_ERR_EVENT 131 
#define  MGMT_ERR_EVENT 130 
#define  PCI_ERR_ANON_BUF_RD 129 
#define  SOFT_ECC_ERROR_EVENT 128 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ql_queue_asic_error (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_queue_fw_error (struct ql_adapter*) ; 
 int /*<<< orphan*/  rx_err ; 

__attribute__((used)) static void ql_process_chip_ae_intr(struct ql_adapter *qdev,
				    struct ib_ae_iocb_rsp *ib_ae_rsp)
{
	switch (ib_ae_rsp->event) {
	case MGMT_ERR_EVENT:
		netif_err(qdev, rx_err, qdev->ndev,
			  "Management Processor Fatal Error.\n");
		ql_queue_fw_error(qdev);
		return;

	case CAM_LOOKUP_ERR_EVENT:
		netdev_err(qdev->ndev, "Multiple CAM hits lookup occurred.\n");
		netdev_err(qdev->ndev, "This event shouldn't occur.\n");
		ql_queue_asic_error(qdev);
		return;

	case SOFT_ECC_ERROR_EVENT:
		netdev_err(qdev->ndev, "Soft ECC error detected.\n");
		ql_queue_asic_error(qdev);
		break;

	case PCI_ERR_ANON_BUF_RD:
		netdev_err(qdev->ndev, "PCI error occurred when reading "
					"anonymous buffers from rx_ring %d.\n",
					ib_ae_rsp->q_id);
		ql_queue_asic_error(qdev);
		break;

	default:
		netif_err(qdev, drv, qdev->ndev, "Unexpected event %d.\n",
			  ib_ae_rsp->event);
		ql_queue_asic_error(qdev);
		break;
	}
}