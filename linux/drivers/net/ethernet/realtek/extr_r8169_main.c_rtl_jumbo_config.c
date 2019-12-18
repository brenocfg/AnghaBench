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
 int ETH_DATA_LEN ; 
 int /*<<< orphan*/  rtl_hw_jumbo_disable (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_jumbo_enable (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_jumbo_config(struct rtl8169_private *tp, int mtu)
{
	if (mtu > ETH_DATA_LEN)
		rtl_hw_jumbo_enable(tp);
	else
		rtl_hw_jumbo_disable(tp);
}