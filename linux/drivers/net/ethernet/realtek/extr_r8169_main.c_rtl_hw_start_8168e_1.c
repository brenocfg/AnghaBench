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
 int /*<<< orphan*/  Config5 ; 
 int /*<<< orphan*/  MISC ; 
 int RTL_R32 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int Spi_en ; 
 int TXPLA_RST ; 
 int /*<<< orphan*/  rtl_disable_clock_request (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_ephy_init (struct rtl8169_private*,struct ephy_info const*) ; 
 int /*<<< orphan*/  rtl_set_def_aspm_entry_latency (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_hw_start_8168e_1(struct rtl8169_private *tp)
{
	static const struct ephy_info e_info_8168e_1[] = {
		{ 0x00, 0x0200,	0x0100 },
		{ 0x00, 0x0000,	0x0004 },
		{ 0x06, 0x0002,	0x0001 },
		{ 0x06, 0x0000,	0x0030 },
		{ 0x07, 0x0000,	0x2000 },
		{ 0x00, 0x0000,	0x0020 },
		{ 0x03, 0x5800,	0x2000 },
		{ 0x03, 0x0000,	0x0001 },
		{ 0x01, 0x0800,	0x1000 },
		{ 0x07, 0x0000,	0x4000 },
		{ 0x1e, 0x0000,	0x2000 },
		{ 0x19, 0xffff,	0xfe6c },
		{ 0x0a, 0x0000,	0x0040 }
	};

	rtl_set_def_aspm_entry_latency(tp);

	rtl_ephy_init(tp, e_info_8168e_1);

	rtl_disable_clock_request(tp);

	/* Reset tx FIFO pointer */
	RTL_W32(tp, MISC, RTL_R32(tp, MISC) | TXPLA_RST);
	RTL_W32(tp, MISC, RTL_R32(tp, MISC) & ~TXPLA_RST);

	RTL_W8(tp, Config5, RTL_R8(tp, Config5) & ~Spi_en);
}