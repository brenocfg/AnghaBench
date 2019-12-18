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
struct ephy_info {int member_0; int member_1; int member_2; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  Config5 ; 
 int /*<<< orphan*/  DLLPR ; 
 int /*<<< orphan*/  ERIAR_MASK_0001 ; 
 int /*<<< orphan*/  ERIAR_MASK_0011 ; 
 int /*<<< orphan*/  ERIAR_MASK_1111 ; 
 int /*<<< orphan*/  MCU ; 
 int /*<<< orphan*/  MISC ; 
 int NOW_IS_OOB ; 
 int PFM_EN ; 
 int PWM_EN ; 
 int RTL_R32 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int Spi_en ; 
 int /*<<< orphan*/  rtl8168_config_eee_mac (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_disable_clock_request (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_ephy_init (struct rtl8169_private*,struct ephy_info const*) ; 
 int /*<<< orphan*/  rtl_eri_set_bits (struct rtl8169_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_eri_write (struct rtl8169_private*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_hw_aspm_clkreq_enable (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  rtl_set_def_aspm_entry_latency (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_set_fifo_size (struct rtl8169_private*,int,int,int,int) ; 
 int /*<<< orphan*/  rtl_w0w1_eri (struct rtl8169_private*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtl_hw_start_8168e_2(struct rtl8169_private *tp)
{
	static const struct ephy_info e_info_8168e_2[] = {
		{ 0x09, 0x0000,	0x0080 },
		{ 0x19, 0x0000,	0x0224 },
		{ 0x00, 0x0000,	0x0004 },
		{ 0x0c, 0x3df0,	0x0200 },
	};

	rtl_set_def_aspm_entry_latency(tp);

	rtl_ephy_init(tp, e_info_8168e_2);

	rtl_eri_write(tp, 0xc0, ERIAR_MASK_0011, 0x0000);
	rtl_eri_write(tp, 0xb8, ERIAR_MASK_0011, 0x0000);
	rtl_set_fifo_size(tp, 0x10, 0x10, 0x02, 0x06);
	rtl_eri_write(tp, 0xcc, ERIAR_MASK_1111, 0x00000050);
	rtl_eri_write(tp, 0xd0, ERIAR_MASK_1111, 0x07ff0060);
	rtl_eri_set_bits(tp, 0x1b0, ERIAR_MASK_0001, BIT(4));
	rtl_w0w1_eri(tp, 0x0d4, ERIAR_MASK_0011, 0x0c00, 0xff00);

	rtl_disable_clock_request(tp);

	RTL_W8(tp, MCU, RTL_R8(tp, MCU) & ~NOW_IS_OOB);

	rtl8168_config_eee_mac(tp);

	RTL_W8(tp, DLLPR, RTL_R8(tp, DLLPR) | PFM_EN);
	RTL_W32(tp, MISC, RTL_R32(tp, MISC) | PWM_EN);
	RTL_W8(tp, Config5, RTL_R8(tp, Config5) & ~Spi_en);

	rtl_hw_aspm_clkreq_enable(tp, true);
}