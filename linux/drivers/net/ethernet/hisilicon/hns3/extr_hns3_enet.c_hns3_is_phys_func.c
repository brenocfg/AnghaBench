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
struct pci_dev {int device; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  HNAE3_DEV_ID_100G_RDMA_DCB_PFC_VF 136 
#define  HNAE3_DEV_ID_100G_RDMA_MACSEC 135 
#define  HNAE3_DEV_ID_100G_VF 134 
#define  HNAE3_DEV_ID_25GE 133 
#define  HNAE3_DEV_ID_25GE_RDMA 132 
#define  HNAE3_DEV_ID_25GE_RDMA_MACSEC 131 
#define  HNAE3_DEV_ID_50GE_RDMA 130 
#define  HNAE3_DEV_ID_50GE_RDMA_MACSEC 129 
#define  HNAE3_DEV_ID_GE 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 

bool hns3_is_phys_func(struct pci_dev *pdev)
{
	u32 dev_id = pdev->device;

	switch (dev_id) {
	case HNAE3_DEV_ID_GE:
	case HNAE3_DEV_ID_25GE:
	case HNAE3_DEV_ID_25GE_RDMA:
	case HNAE3_DEV_ID_25GE_RDMA_MACSEC:
	case HNAE3_DEV_ID_50GE_RDMA:
	case HNAE3_DEV_ID_50GE_RDMA_MACSEC:
	case HNAE3_DEV_ID_100G_RDMA_MACSEC:
		return true;
	case HNAE3_DEV_ID_100G_VF:
	case HNAE3_DEV_ID_100G_RDMA_DCB_PFC_VF:
		return false;
	default:
		dev_warn(&pdev->dev, "un-recognized pci device-id %d",
			 dev_id);
	}

	return false;
}