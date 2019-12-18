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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int r8168_mac_ocp_read (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8168_mac_ocp_write (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void r8168_mac_ocp_modify(struct rtl8169_private *tp, u32 reg, u16 mask,
				 u16 set)
{
	u16 data = r8168_mac_ocp_read(tp, reg);

	r8168_mac_ocp_write(tp, reg, (data & ~mask) | set);
}