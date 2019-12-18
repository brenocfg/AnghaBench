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
typedef  int u16 ;
struct r8152 {int coalesce; int /*<<< orphan*/  flags; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int AUTOLOAD_DONE ; 
 int BMCR_PDOWN ; 
 int /*<<< orphan*/  GREEN_ETHERNET ; 
 int MAC_CLK_SPDWN_EN ; 
 int /*<<< orphan*/  MCU_TYPE_PLA ; 
 int /*<<< orphan*/  MCU_TYPE_USB ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  PHY_STAT_LAN_ON ; 
 int /*<<< orphan*/  PLA_BOOT_CTRL ; 
 int /*<<< orphan*/  PLA_MAC_PWR_CTRL2 ; 
 int /*<<< orphan*/  RTL8152_UNPLUG ; 
 int RX_AGG_DISABLE ; 
 int RX_ZERO_EN ; 
 int /*<<< orphan*/  USB_MSC_TIMER ; 
 int /*<<< orphan*/  USB_U1U2_TIMER ; 
 int /*<<< orphan*/  USB_USB_CTRL ; 
 int /*<<< orphan*/  msleep (int) ; 
 int ocp_read_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocp_write_word (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int r8152_mdio_read (struct r8152*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8152_mdio_write (struct r8152*,int /*<<< orphan*/ ,int) ; 
 int r8153_phy_status (struct r8152*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8153_queue_wake (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153_u2p3en (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153b_power_cut_en (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153b_u1u2en (struct r8152*,int) ; 
 int /*<<< orphan*/  r8153b_ups_en (struct r8152*,int) ; 
 int /*<<< orphan*/  rtl_runtime_suspend_enable (struct r8152*,int) ; 
 int /*<<< orphan*/  rtl_tally_reset (struct r8152*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_enable_lpm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r8153b_init(struct r8152 *tp)
{
	u32 ocp_data;
	u16 data;
	int i;

	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return;

	r8153b_u1u2en(tp, false);

	for (i = 0; i < 500; i++) {
		if (ocp_read_word(tp, MCU_TYPE_PLA, PLA_BOOT_CTRL) &
		    AUTOLOAD_DONE)
			break;
		msleep(20);
	}

	data = r8153_phy_status(tp, 0);

	data = r8152_mdio_read(tp, MII_BMCR);
	if (data & BMCR_PDOWN) {
		data &= ~BMCR_PDOWN;
		r8152_mdio_write(tp, MII_BMCR, data);
	}

	data = r8153_phy_status(tp, PHY_STAT_LAN_ON);

	r8153_u2p3en(tp, false);

	/* MSC timer = 0xfff * 8ms = 32760 ms */
	ocp_write_word(tp, MCU_TYPE_USB, USB_MSC_TIMER, 0x0fff);

	/* U1/U2/L1 idle timer. 500 us */
	ocp_write_word(tp, MCU_TYPE_USB, USB_U1U2_TIMER, 500);

	r8153b_power_cut_en(tp, false);
	r8153b_ups_en(tp, false);
	r8153_queue_wake(tp, false);
	rtl_runtime_suspend_enable(tp, false);
	r8153b_u1u2en(tp, true);
	usb_enable_lpm(tp->udev);

	/* MAC clock speed down */
	ocp_data = ocp_read_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL2);
	ocp_data |= MAC_CLK_SPDWN_EN;
	ocp_write_word(tp, MCU_TYPE_PLA, PLA_MAC_PWR_CTRL2, ocp_data);

	set_bit(GREEN_ETHERNET, &tp->flags);

	/* rx aggregation */
	ocp_data = ocp_read_word(tp, MCU_TYPE_USB, USB_USB_CTRL);
	ocp_data &= ~(RX_AGG_DISABLE | RX_ZERO_EN);
	ocp_write_word(tp, MCU_TYPE_USB, USB_USB_CTRL, ocp_data);

	rtl_tally_reset(tp);

	tp->coalesce = 15000;	/* 15 us */
}