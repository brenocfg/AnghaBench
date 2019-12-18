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
 int /*<<< orphan*/  ChipCmd ; 
 int /*<<< orphan*/  RTL_R8 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_ack_events (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  rtl_irq_disable (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl8169_irq_mask_and_ack(struct rtl8169_private *tp)
{
	rtl_irq_disable(tp);
	rtl_ack_events(tp, 0xffffffff);
	/* PCI commit */
	RTL_R8(tp, ChipCmd);
}