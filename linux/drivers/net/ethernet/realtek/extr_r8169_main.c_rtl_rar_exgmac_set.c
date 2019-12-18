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
typedef  int u8 ;
typedef  int u16 ;
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERIAR_MASK_1111 ; 
 int /*<<< orphan*/  rtl_eri_write (struct rtl8169_private*,int,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static void rtl_rar_exgmac_set(struct rtl8169_private *tp, u8 *addr)
{
	const u16 w[] = {
		addr[0] | (addr[1] << 8),
		addr[2] | (addr[3] << 8),
		addr[4] | (addr[5] << 8)
	};

	rtl_eri_write(tp, 0xe0, ERIAR_MASK_1111, w[0] | (w[1] << 16));
	rtl_eri_write(tp, 0xe4, ERIAR_MASK_1111, w[2]);
	rtl_eri_write(tp, 0xf0, ERIAR_MASK_1111, w[0] << 16);
	rtl_eri_write(tp, 0xf4, ERIAR_MASK_1111, w[1] | (w[2] << 16));
}