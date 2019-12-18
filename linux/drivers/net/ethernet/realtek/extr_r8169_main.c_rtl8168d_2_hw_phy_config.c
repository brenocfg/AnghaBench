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
struct rtl8169_private {int dummy; } ;
struct phy_reg {int member_0; int member_1; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  MII_EXPANSION ; 
 struct phy_reg const* rtl8168d_1_phy_reg_init_0 ; 
 struct phy_reg const* rtl8168d_1_phy_reg_init_1 ; 
 int rtl8168d_efuse_read (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  rtl_apply_firmware_cond (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_patchphy (struct rtl8169_private*,int,int) ; 
 int rtl_readphy (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  rtl_w0w1_phy (struct rtl8169_private*,int,int,int) ; 
 int /*<<< orphan*/  rtl_writephy (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  rtl_writephy_batch (struct rtl8169_private*,struct phy_reg const*) ; 

__attribute__((used)) static void rtl8168d_2_hw_phy_config(struct rtl8169_private *tp)
{
	rtl_writephy_batch(tp, rtl8168d_1_phy_reg_init_0);

	if (rtl8168d_efuse_read(tp, 0x01) == 0xb1) {
		int val;

		rtl_writephy_batch(tp, rtl8168d_1_phy_reg_init_1);

		val = rtl_readphy(tp, 0x0d);
		if ((val & 0x00ff) != 0x006c) {
			static const u32 set[] = {
				0x0065, 0x0066, 0x0067, 0x0068,
				0x0069, 0x006a, 0x006b, 0x006c
			};
			int i;

			rtl_writephy(tp, 0x1f, 0x0002);

			val &= 0xff00;
			for (i = 0; i < ARRAY_SIZE(set); i++)
				rtl_writephy(tp, 0x0d, val | set[i]);
		}
	} else {
		static const struct phy_reg phy_reg_init[] = {
			{ 0x1f, 0x0002 },
			{ 0x05, 0x2642 },
			{ 0x1f, 0x0005 },
			{ 0x05, 0x8330 },
			{ 0x06, 0x2642 }
		};

		rtl_writephy_batch(tp, phy_reg_init);
	}

	/* Fine tune PLL performance */
	rtl_writephy(tp, 0x1f, 0x0002);
	rtl_w0w1_phy(tp, 0x02, 0x0100, 0x0600);
	rtl_w0w1_phy(tp, 0x03, 0x0000, 0xe000);

	/* Switching regulator Slew rate */
	rtl_writephy(tp, 0x1f, 0x0002);
	rtl_patchphy(tp, 0x0f, 0x0017);

	rtl_writephy(tp, 0x1f, 0x0005);
	rtl_writephy(tp, 0x05, 0x001b);

	rtl_apply_firmware_cond(tp, MII_EXPANSION, 0xb300);

	rtl_writephy(tp, 0x1f, 0x0000);
}