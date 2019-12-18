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
 int /*<<< orphan*/  ERIAR_MASK_0001 ; 
 int /*<<< orphan*/  rtl_eri_write (struct rtl8169_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8168g_set_pause_thresholds(struct rtl8169_private *tp,
					  u8 low, u8 high)
{
	/* FIFO thresholds for pause flow control */
	rtl_eri_write(tp, 0xcc, ERIAR_MASK_0001, low);
	rtl_eri_write(tp, 0xd0, ERIAR_MASK_0001, high);
}