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
 int /*<<< orphan*/  ERIAR_EXGMAC ; 
 int /*<<< orphan*/  _rtl_eri_read (struct rtl8169_private*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 rtl_eri_read(struct rtl8169_private *tp, int addr)
{
	return _rtl_eri_read(tp, addr, ERIAR_EXGMAC);
}