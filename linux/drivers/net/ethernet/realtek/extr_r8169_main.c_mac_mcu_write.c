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
struct rtl8169_private {int ocp_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  r8168_mac_ocp_write (struct rtl8169_private*,int,int) ; 

__attribute__((used)) static void mac_mcu_write(struct rtl8169_private *tp, int reg, int value)
{
	if (reg == 0x1f) {
		tp->ocp_base = value << 4;
		return;
	}

	r8168_mac_ocp_write(tp, tp->ocp_base + reg, value);
}