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
#define  RTL_GIGA_MAC_VER_27 133 
#define  RTL_GIGA_MAC_VER_28 132 
#define  RTL_GIGA_MAC_VER_31 131 
#define  RTL_GIGA_MAC_VER_49 130 
#define  RTL_GIGA_MAC_VER_50 129 
#define  RTL_GIGA_MAC_VER_51 128 
 int r8168dp_check_dash (struct rtl8169_private*) ; 
 int r8168ep_check_dash (struct rtl8169_private*) ; 

__attribute__((used)) static bool r8168_check_dash(struct rtl8169_private *tp)
{
	switch (tp->mac_version) {
	case RTL_GIGA_MAC_VER_27:
	case RTL_GIGA_MAC_VER_28:
	case RTL_GIGA_MAC_VER_31:
		return r8168dp_check_dash(tp);
	case RTL_GIGA_MAC_VER_49:
	case RTL_GIGA_MAC_VER_50:
	case RTL_GIGA_MAC_VER_51:
		return r8168ep_check_dash(tp);
	default:
		return false;
	}
}