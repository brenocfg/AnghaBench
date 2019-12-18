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
struct hl_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int GOYA_ASYNC_EVENT_ID_PI_UPDATE ; 
#define  GOYA_QUEUE_ID_CPU_PQ 142 
#define  GOYA_QUEUE_ID_DMA_0 141 
#define  GOYA_QUEUE_ID_DMA_1 140 
#define  GOYA_QUEUE_ID_DMA_2 139 
#define  GOYA_QUEUE_ID_DMA_3 138 
#define  GOYA_QUEUE_ID_DMA_4 137 
#define  GOYA_QUEUE_ID_MME 136 
#define  GOYA_QUEUE_ID_TPC0 135 
#define  GOYA_QUEUE_ID_TPC1 134 
#define  GOYA_QUEUE_ID_TPC2 133 
#define  GOYA_QUEUE_ID_TPC3 132 
#define  GOYA_QUEUE_ID_TPC4 131 
#define  GOYA_QUEUE_ID_TPC5 130 
#define  GOYA_QUEUE_ID_TPC6 129 
#define  GOYA_QUEUE_ID_TPC7 128 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int mmCPU_IF_PF_PQ_PI ; 
 int mmDMA_QM_0_PQ_PI ; 
 int mmDMA_QM_1_PQ_PI ; 
 int mmDMA_QM_2_PQ_PI ; 
 int mmDMA_QM_3_PQ_PI ; 
 int mmDMA_QM_4_PQ_PI ; 
 int mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR ; 
 int mmMME_QM_PQ_PI ; 
 int mmTPC0_QM_PQ_PI ; 
 int mmTPC1_QM_PQ_PI ; 
 int mmTPC2_QM_PQ_PI ; 
 int mmTPC3_QM_PQ_PI ; 
 int mmTPC4_QM_PQ_PI ; 
 int mmTPC5_QM_PQ_PI ; 
 int mmTPC6_QM_PQ_PI ; 
 int mmTPC7_QM_PQ_PI ; 

void goya_ring_doorbell(struct hl_device *hdev, u32 hw_queue_id, u32 pi)
{
	u32 db_reg_offset, db_value;

	switch (hw_queue_id) {
	case GOYA_QUEUE_ID_DMA_0:
		db_reg_offset = mmDMA_QM_0_PQ_PI;
		break;

	case GOYA_QUEUE_ID_DMA_1:
		db_reg_offset = mmDMA_QM_1_PQ_PI;
		break;

	case GOYA_QUEUE_ID_DMA_2:
		db_reg_offset = mmDMA_QM_2_PQ_PI;
		break;

	case GOYA_QUEUE_ID_DMA_3:
		db_reg_offset = mmDMA_QM_3_PQ_PI;
		break;

	case GOYA_QUEUE_ID_DMA_4:
		db_reg_offset = mmDMA_QM_4_PQ_PI;
		break;

	case GOYA_QUEUE_ID_CPU_PQ:
		db_reg_offset = mmCPU_IF_PF_PQ_PI;
		break;

	case GOYA_QUEUE_ID_MME:
		db_reg_offset = mmMME_QM_PQ_PI;
		break;

	case GOYA_QUEUE_ID_TPC0:
		db_reg_offset = mmTPC0_QM_PQ_PI;
		break;

	case GOYA_QUEUE_ID_TPC1:
		db_reg_offset = mmTPC1_QM_PQ_PI;
		break;

	case GOYA_QUEUE_ID_TPC2:
		db_reg_offset = mmTPC2_QM_PQ_PI;
		break;

	case GOYA_QUEUE_ID_TPC3:
		db_reg_offset = mmTPC3_QM_PQ_PI;
		break;

	case GOYA_QUEUE_ID_TPC4:
		db_reg_offset = mmTPC4_QM_PQ_PI;
		break;

	case GOYA_QUEUE_ID_TPC5:
		db_reg_offset = mmTPC5_QM_PQ_PI;
		break;

	case GOYA_QUEUE_ID_TPC6:
		db_reg_offset = mmTPC6_QM_PQ_PI;
		break;

	case GOYA_QUEUE_ID_TPC7:
		db_reg_offset = mmTPC7_QM_PQ_PI;
		break;

	default:
		/* Should never get here */
		dev_err(hdev->dev, "H/W queue %d is invalid. Can't set pi\n",
			hw_queue_id);
		return;
	}

	db_value = pi;

	/* ring the doorbell */
	WREG32(db_reg_offset, db_value);

	if (hw_queue_id == GOYA_QUEUE_ID_CPU_PQ)
		WREG32(mmGIC_DISTRIBUTOR__5_GICD_SETSPI_NSR,
				GOYA_ASYNC_EVENT_ID_PI_UPDATE);
}