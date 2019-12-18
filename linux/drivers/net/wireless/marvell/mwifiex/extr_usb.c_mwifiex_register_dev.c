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
struct usb_card_rec {TYPE_2__* udev; struct mwifiex_adapter* adapter; } ;
struct mwifiex_adapter {int ext_scan; int usb_mc_status; int usb_mc_setup; int /*<<< orphan*/  fw_name; void* tx_buf_size; scalar_t__ card; } ;
struct TYPE_3__ {int /*<<< orphan*/  idProduct; } ;
struct TYPE_4__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 void* MWIFIEX_TX_DATA_BUF_SIZE_2K ; 
 void* MWIFIEX_TX_DATA_BUF_SIZE_4K ; 
 int /*<<< orphan*/  USB8766_DEFAULT_FW_NAME ; 
#define  USB8766_PID_1 135 
#define  USB8766_PID_2 134 
 int /*<<< orphan*/  USB8797_DEFAULT_FW_NAME ; 
#define  USB8797_PID_1 133 
#define  USB8797_PID_2 132 
 int /*<<< orphan*/  USB8801_DEFAULT_FW_NAME ; 
#define  USB8801_PID_1 131 
#define  USB8801_PID_2 130 
 int /*<<< orphan*/  USB8997_DEFAULT_FW_NAME ; 
#define  USB8997_PID_1 129 
#define  USB8997_PID_2 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mwifiex_register_dev(struct mwifiex_adapter *adapter)
{
	struct usb_card_rec *card = (struct usb_card_rec *)adapter->card;

	card->adapter = adapter;

	switch (le16_to_cpu(card->udev->descriptor.idProduct)) {
	case USB8997_PID_1:
	case USB8997_PID_2:
		adapter->tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_4K;
		strcpy(adapter->fw_name, USB8997_DEFAULT_FW_NAME);
		adapter->ext_scan = true;
		break;
	case USB8766_PID_1:
	case USB8766_PID_2:
		adapter->tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K;
		strcpy(adapter->fw_name, USB8766_DEFAULT_FW_NAME);
		adapter->ext_scan = true;
		break;
	case USB8801_PID_1:
	case USB8801_PID_2:
		adapter->tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K;
		strcpy(adapter->fw_name, USB8801_DEFAULT_FW_NAME);
		adapter->ext_scan = false;
		break;
	case USB8797_PID_1:
	case USB8797_PID_2:
	default:
		adapter->tx_buf_size = MWIFIEX_TX_DATA_BUF_SIZE_2K;
		strcpy(adapter->fw_name, USB8797_DEFAULT_FW_NAME);
		break;
	}

	adapter->usb_mc_status = false;
	adapter->usb_mc_setup = false;

	return 0;
}