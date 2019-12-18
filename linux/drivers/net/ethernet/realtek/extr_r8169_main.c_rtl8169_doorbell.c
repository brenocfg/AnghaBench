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
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NPQ ; 
 int /*<<< orphan*/  RTL_W16 (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TxPoll ; 
 int /*<<< orphan*/  TxPoll_8125 ; 
 scalar_t__ rtl_is_8125 (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl8169_doorbell(struct rtl8169_private *tp)
{
	if (rtl_is_8125(tp))
		RTL_W16(tp, TxPoll_8125, BIT(0));
	else
		RTL_W8(tp, TxPoll, NPQ);
}