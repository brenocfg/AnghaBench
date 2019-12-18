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
struct rtl8169_private {int mac_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  RTL_GIGA_MAC_VER_27 133 
#define  RTL_GIGA_MAC_VER_28 132 
#define  RTL_GIGA_MAC_VER_31 131 
#define  RTL_GIGA_MAC_VER_49 130 
#define  RTL_GIGA_MAC_VER_50 129 
#define  RTL_GIGA_MAC_VER_51 128 
 int /*<<< orphan*/  rtl8168dp_driver_start (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8168ep_driver_start (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl8168_driver_start(struct rtl8169_private *tp)
{
	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_27:
	case RTL_GIGA_MAC_VER_28:
	case RTL_GIGA_MAC_VER_31:
		rtl8168dp_driver_start(tp);
		break;
	case RTL_GIGA_MAC_VER_49:
	case RTL_GIGA_MAC_VER_50:
	case RTL_GIGA_MAC_VER_51:
		rtl8168ep_driver_start(tp);
		break;
	default:
		BUG();
		break;
	}
}