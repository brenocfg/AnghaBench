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
 int /*<<< orphan*/  ERIAR_MASK_0011 ; 
 int /*<<< orphan*/  rtl_ephy_init (struct rtl8169_private*,struct ephy_info const*) ; 
 int /*<<< orphan*/  rtl_eri_set_bits (struct rtl8169_private*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_hw_start_8168f (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_pcie_state_l2l3_disable (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_hw_start_8411(struct rtl8169_private *tp)
{
	static const struct ephy_info e_info_8168f_1[] = {
		{ 0x06, 0x00c0,	0x0020 },
		{ 0x0f, 0xffff,	0x5200 },
		{ 0x19, 0x0000,	0x0224 },
		{ 0x00, 0x0000,	0x0004 },
		{ 0x0c, 0x3df0,	0x0200 },
	};

	rtl_hw_start_8168f(tp);
	rtl_pcie_state_l2l3_disable(tp);

	rtl_ephy_init(tp, e_info_8168f_1);

	rtl_eri_set_bits(tp, 0x0d4, ERIAR_MASK_0011, 0x0c00);
}