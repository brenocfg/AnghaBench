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
 int /*<<< orphan*/  ERIAR ; 
 int ERIAR_MASK_1111 ; 
 int ERIAR_READ_CMD ; 
 int /*<<< orphan*/  ERIDR ; 
 int /*<<< orphan*/  RTL_R32 (struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTL_W32 (struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_eriar_cond ; 
 scalar_t__ rtl_udelay_loop_wait_high (struct rtl8169_private*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static u32 _rtl_eri_read(struct rtl8169_private *tp, int addr, int type)
{
	RTL_W32(tp, ERIAR, ERIAR_READ_CMD | type | ERIAR_MASK_1111 | addr);

	return rtl_udelay_loop_wait_high(tp, &rtl_eriar_cond, 100, 100) ?
		RTL_R32(tp, ERIDR) : ~0;
}