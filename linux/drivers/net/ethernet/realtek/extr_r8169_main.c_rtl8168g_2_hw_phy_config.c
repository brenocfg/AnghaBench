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
 int /*<<< orphan*/  rtl8168g_config_eee_phy (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_apply_firmware (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_enable_eee (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl8168g_2_hw_phy_config(struct rtl8169_private *tp)
{
	rtl_apply_firmware(tp);
	rtl8168g_config_eee_phy(tp);
	rtl_enable_eee(tp);
}