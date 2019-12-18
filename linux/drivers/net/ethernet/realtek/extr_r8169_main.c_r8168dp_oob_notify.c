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
 int /*<<< orphan*/  r8168dp_ocp_write (struct rtl8169_private*,int,int,int) ; 
 int /*<<< orphan*/  rtl_eri_write (struct rtl8169_private*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r8168dp_oob_notify(struct rtl8169_private *tp, u8 cmd)
{
	rtl_eri_write(tp, 0xe8, ERIAR_MASK_0001, cmd);

	r8168dp_ocp_write(tp, 0x1, 0x30, 0x00000001);
}