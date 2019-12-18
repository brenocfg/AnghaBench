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
struct rtl8169_private {int /*<<< orphan*/  phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  phy_modify_paged (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int r8168_mac_ocp_read (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  r8168_mac_ocp_write (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  rtl8168g_config_eee_phy (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168g_disable_aldps (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_apply_firmware (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_enable_eee (struct rtl8169_private*) ; 
 int rtl_readphy (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  rtl_w0w1_phy (struct rtl8169_private*,int,int,int) ; 
 int /*<<< orphan*/  rtl_writephy (struct rtl8169_private*,int,int) ; 

__attribute__((used)) static void rtl8168h_2_hw_phy_config(struct rtl8169_private *tp)
{
	u16 ioffset_p3, ioffset_p2, ioffset_p1, ioffset_p0;
	u16 rlen;
	u32 data;

	rtl_apply_firmware(tp);

	/* CHIN EST parameter update */
	rtl_writephy(tp, 0x1f, 0x0a43);
	rtl_writephy(tp, 0x13, 0x808a);
	rtl_w0w1_phy(tp, 0x14, 0x000a, 0x003f);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* enable R-tune & PGA-retune function */
	rtl_writephy(tp, 0x1f, 0x0a43);
	rtl_writephy(tp, 0x13, 0x0811);
	rtl_w0w1_phy(tp, 0x14, 0x0800, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0a42);
	rtl_w0w1_phy(tp, 0x16, 0x0002, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* enable GPHY 10M */
	phy_modify_paged(tp->phydev, 0x0a44, 0x11, 0, BIT(11));

	r8168_mac_ocp_write(tp, 0xdd02, 0x807d);
	data = r8168_mac_ocp_read(tp, 0xdd02);
	ioffset_p3 = ((data & 0x80)>>7);
	ioffset_p3 <<= 3;

	data = r8168_mac_ocp_read(tp, 0xdd00);
	ioffset_p3 |= ((data & (0xe000))>>13);
	ioffset_p2 = ((data & (0x1e00))>>9);
	ioffset_p1 = ((data & (0x01e0))>>5);
	ioffset_p0 = ((data & 0x0010)>>4);
	ioffset_p0 <<= 3;
	ioffset_p0 |= (data & (0x07));
	data = (ioffset_p3<<12)|(ioffset_p2<<8)|(ioffset_p1<<4)|(ioffset_p0);

	if ((ioffset_p3 != 0x0f) || (ioffset_p2 != 0x0f) ||
	    (ioffset_p1 != 0x0f) || (ioffset_p0 != 0x0f)) {
		rtl_writephy(tp, 0x1f, 0x0bcf);
		rtl_writephy(tp, 0x16, data);
		rtl_writephy(tp, 0x1f, 0x0000);
	}

	/* Modify rlen (TX LPF corner frequency) level */
	rtl_writephy(tp, 0x1f, 0x0bcd);
	data = rtl_readphy(tp, 0x16);
	data &= 0x000f;
	rlen = 0;
	if (data > 3)
		rlen = data - 3;
	data = rlen | (rlen<<4) | (rlen<<8) | (rlen<<12);
	rtl_writephy(tp, 0x17, data);
	rtl_writephy(tp, 0x1f, 0x0bcd);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* disable phy pfm mode */
	phy_modify_paged(tp->phydev, 0x0a44, 0x11, BIT(7), 0);

	rtl8168g_disable_aldps(tp);
	rtl8168g_config_eee_phy(tp);
	rtl_enable_eee(tp);
}