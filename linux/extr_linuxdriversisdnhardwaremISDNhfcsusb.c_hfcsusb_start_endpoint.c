#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_complete_t ;
struct hfcsusb {scalar_t__ cfg_used; TYPE_1__* fifos; } ;
struct TYPE_3__ {scalar_t__ active; } ;

/* Variables and functions */
 scalar_t__ CNF_3INT3ISO ; 
 scalar_t__ CNF_3ISO3ISO ; 
 scalar_t__ CNF_4INT3ISO ; 
 scalar_t__ CNF_4ISO3ISO ; 
 size_t HFCUSB_B1_RX ; 
 int /*<<< orphan*/  HFCUSB_B1_TX ; 
 size_t HFCUSB_B2_RX ; 
 int /*<<< orphan*/  HFCUSB_B2_TX ; 
 size_t HFCUSB_D_RX ; 
 int /*<<< orphan*/  HFCUSB_D_TX ; 
 size_t HFCUSB_PCM_RX ; 
#define  HFC_CHAN_B1 131 
#define  HFC_CHAN_B2 130 
#define  HFC_CHAN_D 129 
#define  HFC_CHAN_E 128 
 int /*<<< orphan*/  ISOC_PACKETS_B ; 
 int /*<<< orphan*/  ISOC_PACKETS_D ; 
 int /*<<< orphan*/  rx_iso_complete ; 
 int /*<<< orphan*/  start_int_fifo (TYPE_1__*) ; 
 int /*<<< orphan*/  start_isoc_chain (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tx_iso_complete ; 

__attribute__((used)) static void
hfcsusb_start_endpoint(struct hfcsusb *hw, int channel)
{
	/* quick check if endpoint already running */
	if ((channel == HFC_CHAN_D) && (hw->fifos[HFCUSB_D_RX].active))
		return;
	if ((channel == HFC_CHAN_B1) && (hw->fifos[HFCUSB_B1_RX].active))
		return;
	if ((channel == HFC_CHAN_B2) && (hw->fifos[HFCUSB_B2_RX].active))
		return;
	if ((channel == HFC_CHAN_E) && (hw->fifos[HFCUSB_PCM_RX].active))
		return;

	/* start rx endpoints using USB INT IN method */
	if (hw->cfg_used == CNF_3INT3ISO || hw->cfg_used == CNF_4INT3ISO)
		start_int_fifo(hw->fifos + channel * 2 + 1);

	/* start rx endpoints using USB ISO IN method */
	if (hw->cfg_used == CNF_3ISO3ISO || hw->cfg_used == CNF_4ISO3ISO) {
		switch (channel) {
		case HFC_CHAN_D:
			start_isoc_chain(hw->fifos + HFCUSB_D_RX,
					 ISOC_PACKETS_D,
					 (usb_complete_t)rx_iso_complete,
					 16);
			break;
		case HFC_CHAN_E:
			start_isoc_chain(hw->fifos + HFCUSB_PCM_RX,
					 ISOC_PACKETS_D,
					 (usb_complete_t)rx_iso_complete,
					 16);
			break;
		case HFC_CHAN_B1:
			start_isoc_chain(hw->fifos + HFCUSB_B1_RX,
					 ISOC_PACKETS_B,
					 (usb_complete_t)rx_iso_complete,
					 16);
			break;
		case HFC_CHAN_B2:
			start_isoc_chain(hw->fifos + HFCUSB_B2_RX,
					 ISOC_PACKETS_B,
					 (usb_complete_t)rx_iso_complete,
					 16);
			break;
		}
	}

	/* start tx endpoints using USB ISO OUT method */
	switch (channel) {
	case HFC_CHAN_D:
		start_isoc_chain(hw->fifos + HFCUSB_D_TX,
				 ISOC_PACKETS_B,
				 (usb_complete_t)tx_iso_complete, 1);
		break;
	case HFC_CHAN_B1:
		start_isoc_chain(hw->fifos + HFCUSB_B1_TX,
				 ISOC_PACKETS_D,
				 (usb_complete_t)tx_iso_complete, 1);
		break;
	case HFC_CHAN_B2:
		start_isoc_chain(hw->fifos + HFCUSB_B2_TX,
				 ISOC_PACKETS_B,
				 (usb_complete_t)tx_iso_complete, 1);
		break;
	}
}