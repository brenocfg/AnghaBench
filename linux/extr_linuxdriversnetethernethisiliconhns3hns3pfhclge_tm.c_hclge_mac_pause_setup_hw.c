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
struct TYPE_2__ {int fc_mode; } ;
struct hclge_dev {TYPE_1__ tm_info; } ;

/* Variables and functions */
#define  HCLGE_FC_FULL 132 
#define  HCLGE_FC_NONE 131 
#define  HCLGE_FC_PFC 130 
#define  HCLGE_FC_RX_PAUSE 129 
#define  HCLGE_FC_TX_PAUSE 128 
 int hclge_mac_pause_en_cfg (struct hclge_dev*,int,int) ; 

__attribute__((used)) static int hclge_mac_pause_setup_hw(struct hclge_dev *hdev)
{
	bool tx_en, rx_en;

	switch (hdev->tm_info.fc_mode) {
	case HCLGE_FC_NONE:
		tx_en = false;
		rx_en = false;
		break;
	case HCLGE_FC_RX_PAUSE:
		tx_en = false;
		rx_en = true;
		break;
	case HCLGE_FC_TX_PAUSE:
		tx_en = true;
		rx_en = false;
		break;
	case HCLGE_FC_FULL:
		tx_en = true;
		rx_en = true;
		break;
	case HCLGE_FC_PFC:
		tx_en = false;
		rx_en = false;
		break;
	default:
		tx_en = true;
		rx_en = true;
	}

	return hclge_mac_pause_en_cfg(hdev, tx_en, rx_en);
}