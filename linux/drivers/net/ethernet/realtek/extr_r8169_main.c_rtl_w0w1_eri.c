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
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int rtl_eri_read (struct rtl8169_private*,int) ; 
 int /*<<< orphan*/  rtl_eri_write (struct rtl8169_private*,int,int,int) ; 

__attribute__((used)) static void rtl_w0w1_eri(struct rtl8169_private *tp, int addr, u32 mask, u32 p,
			 u32 m)
{
	u32 val;

	val = rtl_eri_read(tp, addr);
	rtl_eri_write(tp, addr, mask, (val & ~m) | p);
}