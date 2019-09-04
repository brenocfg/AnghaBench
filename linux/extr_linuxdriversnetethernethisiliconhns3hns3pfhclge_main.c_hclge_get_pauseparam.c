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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct TYPE_2__ {scalar_t__ fc_mode; } ;
struct hclge_dev {TYPE_1__ tm_info; } ;

/* Variables and functions */
 scalar_t__ HCLGE_FC_FULL ; 
 scalar_t__ HCLGE_FC_PFC ; 
 scalar_t__ HCLGE_FC_RX_PAUSE ; 
 scalar_t__ HCLGE_FC_TX_PAUSE ; 
 int hclge_get_autoneg (struct hnae3_handle*) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 

__attribute__((used)) static void hclge_get_pauseparam(struct hnae3_handle *handle, u32 *auto_neg,
				 u32 *rx_en, u32 *tx_en)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;

	*auto_neg = hclge_get_autoneg(handle);

	if (hdev->tm_info.fc_mode == HCLGE_FC_PFC) {
		*rx_en = 0;
		*tx_en = 0;
		return;
	}

	if (hdev->tm_info.fc_mode == HCLGE_FC_RX_PAUSE) {
		*rx_en = 1;
		*tx_en = 0;
	} else if (hdev->tm_info.fc_mode == HCLGE_FC_TX_PAUSE) {
		*tx_en = 1;
		*rx_en = 0;
	} else if (hdev->tm_info.fc_mode == HCLGE_FC_FULL) {
		*rx_en = 1;
		*tx_en = 1;
	} else {
		*rx_en = 0;
		*tx_en = 0;
	}
}