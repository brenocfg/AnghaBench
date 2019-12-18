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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int ERIAR_MASK_SHIFT ; 
 int /*<<< orphan*/  ERIAR_OOB ; 
 int /*<<< orphan*/  _rtl_eri_write (struct rtl8169_private*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r8168ep_ocp_write(struct rtl8169_private *tp, u8 mask, u16 reg,
			      u32 data)
{
	_rtl_eri_write(tp, reg, ((u32)mask & 0x0f) << ERIAR_MASK_SHIFT,
		       data, ERIAR_OOB);
}