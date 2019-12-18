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
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IntrStatus ; 
 int /*<<< orphan*/  IntrStatus_8125 ; 
 int /*<<< orphan*/  RTL_R16 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_R32 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtl_is_8125 (struct rtl8169_private*) ; 

__attribute__((used)) static u32 rtl_get_events(struct rtl8169_private *tp)
{
	if (rtl_is_8125(tp))
		return RTL_R32(tp, IntrStatus_8125);
	else
		return RTL_R16(tp, IntrStatus);
}