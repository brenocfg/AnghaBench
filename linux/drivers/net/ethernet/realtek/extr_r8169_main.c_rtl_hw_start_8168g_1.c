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
 int /*<<< orphan*/  rtl_ephy_init (struct rtl8169_private*,struct ephy_info const*) ; 
 int /*<<< orphan*/  rtl_hw_aspm_clkreq_enable (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  rtl_hw_start_8168g (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_hw_start_8168g_1(struct rtl8169_private *tp)
{
	static const struct ephy_info e_info_8168g_1[] = {
		{ 0x00, 0x0008,	0x0000 },
		{ 0x0c, 0x3ff0,	0x0820 },
		{ 0x1e, 0x0000,	0x0001 },
		{ 0x19, 0x8000,	0x0000 }
	};

	rtl_hw_start_8168g(tp);

	/* disable aspm and clock request before access ephy */
	rtl_hw_aspm_clkreq_enable(tp, false);
	rtl_ephy_init(tp, e_info_8168g_1);
	rtl_hw_aspm_clkreq_enable(tp, true);
}