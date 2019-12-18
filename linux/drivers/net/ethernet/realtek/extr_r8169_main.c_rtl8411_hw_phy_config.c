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
struct rtl8169_private {int dummy; } ;
struct phy_reg {int member_0; int member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl8168f_hw_phy_config (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_apply_firmware (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_w0w1_phy (struct rtl8169_private*,int,int,int) ; 
 int /*<<< orphan*/  rtl_writephy (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  rtl_writephy_batch (struct rtl8169_private*,struct phy_reg const*) ; 

__attribute__((used)) static void rtl8411_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		/* Channel estimation fine tune */
		{ 0x1f, 0x0003 },
		{ 0x09, 0xa20f },
		{ 0x1f, 0x0000 },

		/* Modify green table for giga & fnet */
		{ 0x1f, 0x0005 },
		{ 0x05, 0x8b55 },
		{ 0x06, 0x0000 },
		{ 0x05, 0x8b5e },
		{ 0x06, 0x0000 },
		{ 0x05, 0x8b67 },
		{ 0x06, 0x0000 },
		{ 0x05, 0x8b70 },
		{ 0x06, 0x0000 },
		{ 0x1f, 0x0000 },
		{ 0x1f, 0x0007 },
		{ 0x1e, 0x0078 },
		{ 0x17, 0x0000 },
		{ 0x19, 0x00aa },
		{ 0x1f, 0x0000 },

		/* Modify green table for 10M */
		{ 0x1f, 0x0005 },
		{ 0x05, 0x8b79 },
		{ 0x06, 0xaa00 },
		{ 0x1f, 0x0000 },

		/* Disable hiimpedance detection (RTCT) */
		{ 0x1f, 0x0003 },
		{ 0x01, 0x328a },
		{ 0x1f, 0x0000 }
	};


	rtl_apply_firmware(tp);

	rtl8168f_hw_phy_config(tp);

	/* Improve 2-pair detection performance */
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b85);
	rtl_w0w1_phy(tp, 0x06, 0x4000, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	rtl_writephy_batch(tp, phy_reg_init);

	/* Modify green table for giga */
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b54);
	rtl_w0w1_phy(tp, 0x06, 0x0000, 0x0800);
	rtl_writephy(tp, 0x05, 0x8b5d);
	rtl_w0w1_phy(tp, 0x06, 0x0000, 0x0800);
	rtl_writephy(tp, 0x05, 0x8a7c);
	rtl_w0w1_phy(tp, 0x06, 0x0000, 0x0100);
	rtl_writephy(tp, 0x05, 0x8a7f);
	rtl_w0w1_phy(tp, 0x06, 0x0100, 0x0000);
	rtl_writephy(tp, 0x05, 0x8a82);
	rtl_w0w1_phy(tp, 0x06, 0x0000, 0x0100);
	rtl_writephy(tp, 0x05, 0x8a85);
	rtl_w0w1_phy(tp, 0x06, 0x0000, 0x0100);
	rtl_writephy(tp, 0x05, 0x8a88);
	rtl_w0w1_phy(tp, 0x06, 0x0000, 0x0100);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* uc same-seed solution */
	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x8b85);
	rtl_w0w1_phy(tp, 0x06, 0x8000, 0x0000);
	rtl_writephy(tp, 0x1f, 0x0000);

	/* Green feature */
	rtl_writephy(tp, 0x1f, 0x0003);
	rtl_w0w1_phy(tp, 0x19, 0x0000, 0x0001);
	rtl_w0w1_phy(tp, 0x10, 0x0000, 0x0400);
	rtl_writephy(tp, 0x1f, 0x0000);
}