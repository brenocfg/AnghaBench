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
 int /*<<< orphan*/  rtl_patchphy (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  rtl_writephy (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  rtl_writephy_batch (struct rtl8169_private*,struct phy_reg const*) ; 

__attribute__((used)) static void rtl8168bb_hw_phy_config(struct rtl8169_private *tp)
{
	static const struct phy_reg phy_reg_init[] = {
		{ 0x10, 0xf41b },
		{ 0x1f, 0x0000 }
	};

	rtl_writephy(tp, 0x1f, 0x0001);
	rtl_patchphy(tp, 0x16, 1 << 0);

	rtl_writephy_batch(tp, phy_reg_init);
}