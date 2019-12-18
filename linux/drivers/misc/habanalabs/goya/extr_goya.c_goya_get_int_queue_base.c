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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  sram_base_address; } ;
struct hl_device {int /*<<< orphan*/  dev; scalar_t__* pcie_bar; TYPE_1__ asic_prop; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
#define  GOYA_QUEUE_ID_MME 136 
#define  GOYA_QUEUE_ID_TPC0 135 
#define  GOYA_QUEUE_ID_TPC1 134 
#define  GOYA_QUEUE_ID_TPC2 133 
#define  GOYA_QUEUE_ID_TPC3 132 
#define  GOYA_QUEUE_ID_TPC4 131 
#define  GOYA_QUEUE_ID_TPC5 130 
#define  GOYA_QUEUE_ID_TPC6 129 
#define  GOYA_QUEUE_ID_TPC7 128 
 int MME_QMAN_BASE_OFFSET ; 
 int /*<<< orphan*/  MME_QMAN_LENGTH ; 
 size_t SRAM_CFG_BAR_ID ; 
 int TPC0_QMAN_BASE_OFFSET ; 
 int TPC1_QMAN_BASE_OFFSET ; 
 int TPC2_QMAN_BASE_OFFSET ; 
 int TPC3_QMAN_BASE_OFFSET ; 
 int TPC4_QMAN_BASE_OFFSET ; 
 int TPC5_QMAN_BASE_OFFSET ; 
 int TPC6_QMAN_BASE_OFFSET ; 
 int TPC7_QMAN_BASE_OFFSET ; 
 int /*<<< orphan*/  TPC_QMAN_LENGTH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

void *goya_get_int_queue_base(struct hl_device *hdev, u32 queue_id,
				dma_addr_t *dma_handle,	u16 *queue_len)
{
	void *base;
	u32 offset;

	*dma_handle = hdev->asic_prop.sram_base_address;

	base = (void *) hdev->pcie_bar[SRAM_CFG_BAR_ID];

	switch (queue_id) {
	case GOYA_QUEUE_ID_MME:
		offset = MME_QMAN_BASE_OFFSET;
		*queue_len = MME_QMAN_LENGTH;
		break;
	case GOYA_QUEUE_ID_TPC0:
		offset = TPC0_QMAN_BASE_OFFSET;
		*queue_len = TPC_QMAN_LENGTH;
		break;
	case GOYA_QUEUE_ID_TPC1:
		offset = TPC1_QMAN_BASE_OFFSET;
		*queue_len = TPC_QMAN_LENGTH;
		break;
	case GOYA_QUEUE_ID_TPC2:
		offset = TPC2_QMAN_BASE_OFFSET;
		*queue_len = TPC_QMAN_LENGTH;
		break;
	case GOYA_QUEUE_ID_TPC3:
		offset = TPC3_QMAN_BASE_OFFSET;
		*queue_len = TPC_QMAN_LENGTH;
		break;
	case GOYA_QUEUE_ID_TPC4:
		offset = TPC4_QMAN_BASE_OFFSET;
		*queue_len = TPC_QMAN_LENGTH;
		break;
	case GOYA_QUEUE_ID_TPC5:
		offset = TPC5_QMAN_BASE_OFFSET;
		*queue_len = TPC_QMAN_LENGTH;
		break;
	case GOYA_QUEUE_ID_TPC6:
		offset = TPC6_QMAN_BASE_OFFSET;
		*queue_len = TPC_QMAN_LENGTH;
		break;
	case GOYA_QUEUE_ID_TPC7:
		offset = TPC7_QMAN_BASE_OFFSET;
		*queue_len = TPC_QMAN_LENGTH;
		break;
	default:
		dev_err(hdev->dev, "Got invalid queue id %d\n", queue_id);
		return NULL;
	}

	base += offset;
	*dma_handle += offset;

	return base;
}