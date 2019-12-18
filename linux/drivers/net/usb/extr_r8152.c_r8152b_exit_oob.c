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
typedef  int u32 ;
struct r8152 {TYPE_2__* netdev; TYPE_1__* udev; } ;
struct TYPE_4__ {int features; } ;
struct TYPE_3__ {scalar_t__ speed; } ;

/* Variables and functions */
 int CRWECR_NORAML ; 
 int LINK_LIST_READY ; 
 int MCU_BORW_EN ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int /*<<< orphan*/  MCU_TYPE_USB ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NOW_IS_OOB ; 
 int /*<<< orphan*/  PLA_CR ; 
 int /*<<< orphan*/  PLA_CRWECR ; 
 int /*<<< orphan*/  PLA_OOB_CTRL ; 
 int /*<<< orphan*/  PLA_RCR ; 
 int /*<<< orphan*/  PLA_RMS ; 
 int /*<<< orphan*/  PLA_RXFIFO_CTRL0 ; 
 int /*<<< orphan*/  PLA_RXFIFO_CTRL1 ; 
 int /*<<< orphan*/  PLA_RXFIFO_CTRL2 ; 
 int /*<<< orphan*/  PLA_SFF_STS_7 ; 
 int /*<<< orphan*/  PLA_TCR0 ; 
 int /*<<< orphan*/  PLA_TXFIFO_CTRL ; 
 int RCR_ACPT_ALL ; 
 int RE_INIT_LL ; 
 int RTL8152_RMS ; 
 int RXFIFO_THR1_NORMAL ; 
 int RXFIFO_THR2_FULL ; 
 int RXFIFO_THR2_HIGH ; 
 int RXFIFO_THR3_FULL ; 
 int RXFIFO_THR3_HIGH ; 
 int RX_THR_HIGH ; 
 int TCR0_AUTO_FIFO ; 
 int TEST_MODE_DISABLE ; 
 int TXFIFO_THR_NORMAL ; 
 int TX_AGG_MAX_THRESHOLD ; 
 int TX_SIZE_ADJUST1 ; 
 int /*<<< orphan*/  USB_RX_BUF_TH ; 
 scalar_t__ USB_SPEED_FULL ; 
 scalar_t__ USB_SPEED_LOW ; 
 int /*<<< orphan*/  USB_TX_AGG ; 
 int /*<<< orphan*/  USB_TX_DMA ; 
 int ocp_read_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocp_read_dword (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocp_read_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_byte (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocp_write_dword (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r8153_teredo_off (struct r8152*) ; 
 int /*<<< orphan*/  rtl8152_nic_reset (struct r8152*) ; 
 int /*<<< orphan*/  rtl_rx_vlan_en (struct r8152*,int) ; 
 int /*<<< orphan*/  rxdy_gated_en (struct r8152*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void r8152b_exit_oob(struct r8152 *tp)
{
	u32 ocp_data;
	int i;

	ocp_data = ocp_read_dword(tp, MCU_TYPE_PLA, PLA_RCR);
	ocp_data &= ~RCR_ACPT_ALL;
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RCR, ocp_data);

	rxdy_gated_en(tp, true);
	r8153_teredo_off(tp);
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CRWECR, CRWECR_NORAML);
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_CR, 0x00);

	ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
	ocp_data &= ~NOW_IS_OOB;
	ocp_write_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL, ocp_data);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data &= ~MCU_BORW_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	for (i = 0; i < 1000; i++) {
		ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
		if (ocp_data & LINK_LIST_READY)
			break;
		usleep_range(1000, 2000);
	}

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7);
	ocp_data |= RE_INIT_LL;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_SFF_STS_7, ocp_data);

	for (i = 0; i < 1000; i++) {
		ocp_data = ocp_read_byte(tp, MCU_TYPE_PLA, PLA_OOB_CTRL);
		if (ocp_data & LINK_LIST_READY)
			break;
		usleep_range(1000, 2000);
	}

	rtl8152_nic_reset(tp);

	/* rx share fifo credit full threshold */
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL0, RXFIFO_THR1_NORMAL);

	if (tp->udev->speed == USB_SPEED_FULL ||
	    tp->udev->speed == USB_SPEED_LOW) {
		/* rx share fifo credit near full threshold */
		ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1,
				RXFIFO_THR2_FULL);
		ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2,
				RXFIFO_THR3_FULL);
	} else {
		/* rx share fifo credit near full threshold */
		ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL1,
				RXFIFO_THR2_HIGH);
		ocp_write_dword(tp, MCU_TYPE_PLA, PLA_RXFIFO_CTRL2,
				RXFIFO_THR3_HIGH);
	}

	/* TX share fifo free credit full threshold */
	ocp_write_dword(tp, MCU_TYPE_PLA, PLA_TXFIFO_CTRL, TXFIFO_THR_NORMAL);

	ocp_write_byte(tp, MCU_TYPE_USB, USB_TX_AGG, TX_AGG_MAX_THRESHOLD);
	ocp_write_dword(tp, MCU_TYPE_USB, USB_RX_BUF_TH, RX_THR_HIGH);
	ocp_write_dword(tp, MCU_TYPE_USB, USB_TX_DMA,
			TEST_MODE_DISABLE | TX_SIZE_ADJUST1);

	rtl_rx_vlan_en(tp, tp->netdev->features & NETIF_F_HW_VLAN_CTAG_RX);

	ocp_write_word(tp, MCU_TYPE_PLA, PLA_RMS, RTL8152_RMS);

	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_TCR0);
	ocp_data |= TCR0_AUTO_FIFO;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_TCR0, ocp_data);
}