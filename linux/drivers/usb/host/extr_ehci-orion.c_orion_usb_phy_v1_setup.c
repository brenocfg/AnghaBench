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
struct usb_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CAUSE ; 
 int /*<<< orphan*/  USB_CMD ; 
 int USB_CMD_RESET ; 
 int USB_CMD_RUN ; 
 int /*<<< orphan*/  USB_IPG ; 
 int /*<<< orphan*/  USB_MASK ; 
 int /*<<< orphan*/  USB_MODE ; 
 int USB_MODE_HOST ; 
 int USB_MODE_SDIS ; 
 int /*<<< orphan*/  USB_PHY_IVREF_CTRL ; 
 int /*<<< orphan*/  USB_PHY_PWR_CTRL ; 
 int /*<<< orphan*/  USB_PHY_RX_CTRL ; 
 int /*<<< orphan*/  USB_PHY_TST_GRP_CTRL ; 
 int /*<<< orphan*/  USB_PHY_TX_CTRL ; 
 int rdl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void orion_usb_phy_v1_setup(struct usb_hcd *hcd)
{
	/* The below GLs are according to the Orion Errata document */
	/*
	 * Clear interrupt cause and mask
	 */
	wrl(USB_CAUSE, 0);
	wrl(USB_MASK, 0);

	/*
	 * Reset controller
	 */
	wrl(USB_CMD, rdl(USB_CMD) | USB_CMD_RESET);
	while (rdl(USB_CMD) & USB_CMD_RESET);

	/*
	 * GL# USB-10: Set IPG for non start of frame packets
	 * Bits[14:8]=0xc
	 */
	wrl(USB_IPG, (rdl(USB_IPG) & ~0x7f00) | 0xc00);

	/*
	 * GL# USB-9: USB 2.0 Power Control
	 * BG_VSEL[7:6]=0x1
	 */
	wrl(USB_PHY_PWR_CTRL, (rdl(USB_PHY_PWR_CTRL) & ~0xc0)| 0x40);

	/*
	 * GL# USB-1: USB PHY Tx Control - force calibration to '8'
	 * TXDATA_BLOCK_EN[21]=0x1, EXT_RCAL_EN[13]=0x1, IMP_CAL[6:3]=0x8
	 */
	wrl(USB_PHY_TX_CTRL, (rdl(USB_PHY_TX_CTRL) & ~0x78) | 0x202040);

	/*
	 * GL# USB-3 GL# USB-9: USB PHY Rx Control
	 * RXDATA_BLOCK_LENGHT[31:30]=0x3, EDGE_DET_SEL[27:26]=0,
	 * CDR_FASTLOCK_EN[21]=0, DISCON_THRESHOLD[9:8]=0, SQ_THRESH[7:4]=0x1
	 */
	wrl(USB_PHY_RX_CTRL, (rdl(USB_PHY_RX_CTRL) & ~0xc2003f0) | 0xc0000010);

	/*
	 * GL# USB-3 GL# USB-9: USB PHY IVREF Control
	 * PLLVDD12[1:0]=0x2, RXVDD[5:4]=0x3, Reserved[19]=0
	 */
	wrl(USB_PHY_IVREF_CTRL, (rdl(USB_PHY_IVREF_CTRL) & ~0x80003 ) | 0x32);

	/*
	 * GL# USB-3 GL# USB-9: USB PHY Test Group Control
	 * REG_FIFO_SQ_RST[15]=0
	 */
	wrl(USB_PHY_TST_GRP_CTRL, rdl(USB_PHY_TST_GRP_CTRL) & ~0x8000);

	/*
	 * Stop and reset controller
	 */
	wrl(USB_CMD, rdl(USB_CMD) & ~USB_CMD_RUN);
	wrl(USB_CMD, rdl(USB_CMD) | USB_CMD_RESET);
	while (rdl(USB_CMD) & USB_CMD_RESET);

	/*
	 * GL# USB-5 Streaming disable REG_USB_MODE[4]=1
	 * TBD: This need to be done after each reset!
	 * GL# USB-4 Setup USB Host mode
	 */
	wrl(USB_MODE, USB_MODE_SDIS | USB_MODE_HOST);
}