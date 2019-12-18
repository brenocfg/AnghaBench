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
struct rtl8169_private {scalar_t__ irq_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  IntrMask ; 
 int /*<<< orphan*/  IntrMask_8125 ; 
 int /*<<< orphan*/  RTL_W16 (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtl_is_8125 (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_irq_disable(struct rtl8169_private *tp)
{
	if (rtl_is_8125(tp))
		RTL_W32(tp, IntrMask_8125, 0);
	else
		RTL_W16(tp, IntrMask, 0);
	tp->irq_enabled = 0;
}