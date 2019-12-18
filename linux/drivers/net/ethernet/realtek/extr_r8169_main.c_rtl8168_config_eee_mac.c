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
struct rtl8169_private {scalar_t__ mac_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEE_LED ; 
 int /*<<< orphan*/  ERIAR_MASK_1111 ; 
 scalar_t__ RTL_GIGA_MAC_VER_38 ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_eri_set_bits (struct rtl8169_private*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl8168_config_eee_mac(struct rtl8169_private *tp)
{
	/* Adjust EEE LED frequency */
	if (tp->mac_version != RTL_GIGA_MAC_VER_38)
		RTL_W8(tp, EEE_LED, RTL_R8(tp, EEE_LED) & ~0x07);

	rtl_eri_set_bits(tp, 0x1b0, ERIAR_MASK_1111, 0x0003);
}