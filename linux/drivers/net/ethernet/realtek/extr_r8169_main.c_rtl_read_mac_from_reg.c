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
typedef  int /*<<< orphan*/  u8 ;
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  RTL_R8 (struct rtl8169_private*,int) ; 

__attribute__((used)) static void rtl_read_mac_from_reg(struct rtl8169_private *tp, u8 *mac, int reg)
{
	int i;

	for (i = 0; i < ETH_ALEN; i++)
		mac[i] = RTL_R8(tp, reg + i);
}