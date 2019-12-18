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
 int BIT (int) ; 
 int /*<<< orphan*/  r8168_mac_ocp_modify (struct rtl8169_private*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl8125_config_eee_mac(struct rtl8169_private *tp)
{
	r8168_mac_ocp_modify(tp, 0xe040, 0, BIT(1) | BIT(0));
	r8168_mac_ocp_modify(tp, 0xeb62, 0, BIT(2) | BIT(1));
}