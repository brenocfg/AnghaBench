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
 int /*<<< orphan*/  rtl_hw_start_8125_common (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_set_def_aspm_entry_latency (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_hw_start_8125_2(struct rtl8169_private *tp)
{
	static const struct ephy_info e_info_8125_2[] = {
		{ 0x04, 0xffff, 0xd000 },
		{ 0x0a, 0xffff, 0x8653 },
		{ 0x23, 0xffff, 0xab66 },
		{ 0x20, 0xffff, 0x9455 },
		{ 0x21, 0xffff, 0x99ff },
		{ 0x29, 0xffff, 0xfe04 },

		{ 0x44, 0xffff, 0xd000 },
		{ 0x4a, 0xffff, 0x8653 },
		{ 0x63, 0xffff, 0xab66 },
		{ 0x60, 0xffff, 0x9455 },
		{ 0x61, 0xffff, 0x99ff },
		{ 0x69, 0xffff, 0xfe04 },
	};

	rtl_set_def_aspm_entry_latency(tp);

	/* disable aspm and clock request before access ephy */
	rtl_hw_aspm_clkreq_enable(tp, false);
	rtl_ephy_init(tp, e_info_8125_2);

	rtl_hw_start_8125_common(tp);
}