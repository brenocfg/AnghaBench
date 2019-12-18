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
struct rtl8169_private {scalar_t__ aspm_manageable; } ;

/* Variables and functions */
 int ASPM_en ; 
 int ClkReqEn ; 
 int /*<<< orphan*/  Config2 ; 
 int /*<<< orphan*/  Config5 ; 
 int RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void rtl_hw_aspm_clkreq_enable(struct rtl8169_private *tp, bool enable)
{
	/* Don't enable ASPM in the chip if OS can't control ASPM */
	if (enable && tp->aspm_manageable) {
		RTL_W8(tp, Config5, RTL_R8(tp, Config5) | ASPM_en);
		RTL_W8(tp, Config2, RTL_R8(tp, Config2) | ClkReqEn);
	} else {
		RTL_W8(tp, Config2, RTL_R8(tp, Config2) & ~ClkReqEn);
		RTL_W8(tp, Config5, RTL_R8(tp, Config5) & ~ASPM_en);
	}

	udelay(10);
}