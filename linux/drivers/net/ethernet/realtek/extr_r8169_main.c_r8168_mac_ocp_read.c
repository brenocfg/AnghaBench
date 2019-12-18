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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCPDR ; 
 int /*<<< orphan*/  RTL_R32 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ rtl_ocp_reg_failure (struct rtl8169_private*,int) ; 

__attribute__((used)) static u16 r8168_mac_ocp_read(struct rtl8169_private *tp, u32 reg)
{
	if (rtl_ocp_reg_failure(tp, reg))
		return 0;

	RTL_W32(tp, OCPDR, reg << 15);

	return RTL_R32(tp, OCPDR);
}