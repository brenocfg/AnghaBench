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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ERIAR ; 
 int ERIAR_WRITE_CMD ; 
 int /*<<< orphan*/  ERIDR ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_eriar_cond ; 
 int /*<<< orphan*/  rtl_udelay_loop_wait_low (struct rtl8169_private*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void _rtl_eri_write(struct rtl8169_private *tp, int addr, u32 mask,
			   u32 val, int type)
{
	BUG_ON((addr & 3) || (mask == 0));
	RTL_W32(tp, ERIDR, val);
	RTL_W32(tp, ERIAR, ERIAR_WRITE_CMD | type | mask | addr);

	rtl_udelay_loop_wait_low(tp, &rtl_eriar_cond, 100, 100);
}