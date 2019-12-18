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
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_hw_config (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_hw_start_8125(struct rtl8169_private *tp)
{
	int i;

	/* disable interrupt coalescing */
	for (i = 0xa00; i < 0xb00; i += 4)
		RTL_W32(tp, i, 0);

	rtl_hw_config(tp);
}