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

/* Variables and functions */
 int /*<<< orphan*/  IBCR0 ; 
 int /*<<< orphan*/  IBCR2 ; 
 int /*<<< orphan*/  IBISR0 ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_msleep_loop_wait_high (struct rtl8169_private*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rtl_ocp_tx_cond ; 

__attribute__((used)) static void rtl8168ep_stop_cmac(struct rtl8169_private *tp)
{
	RTL_W8(tp, IBCR2, RTL_R8(tp, IBCR2) & ~0x01);
	rtl_msleep_loop_wait_high(tp, &rtl_ocp_tx_cond, 50, 2000);
	RTL_W8(tp, IBISR0, RTL_R8(tp, IBISR0) | 0x20);
	RTL_W8(tp, IBCR0, RTL_R8(tp, IBCR0) & ~0x01);
}