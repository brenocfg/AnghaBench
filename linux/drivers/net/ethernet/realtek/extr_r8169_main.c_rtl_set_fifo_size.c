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
typedef  int u16 ;
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERIAR_MASK_1111 ; 
 int /*<<< orphan*/  rtl_eri_write (struct rtl8169_private*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl_set_fifo_size(struct rtl8169_private *tp, u16 rx_stat,
			      u16 tx_stat, u16 rx_dyn, u16 tx_dyn)
{
	/* Usage of dynamic vs. static FIFO is controlled by bit
	 * TXCFG_AUTO_FIFO. Exact meaning of FIFO values isn't known.
	 */
	rtl_eri_write(tp, 0xc8, ERIAR_MASK_1111, (rx_stat << 16) | rx_dyn);
	rtl_eri_write(tp, 0xe8, ERIAR_MASK_1111, (tx_stat << 16) | tx_dyn);
}