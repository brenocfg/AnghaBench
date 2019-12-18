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
struct rtl8169_private {int /*<<< orphan*/  Rx_databuff; int /*<<< orphan*/  tx_skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8169_init_ring_indexes (struct rtl8169_private*) ; 
 int rtl8169_rx_fill (struct rtl8169_private*) ; 

__attribute__((used)) static int rtl8169_init_ring(struct rtl8169_private *tp)
{
	rtl8169_init_ring_indexes(tp);

	memset(tp->tx_skb, 0, sizeof(tp->tx_skb));
	memset(tp->Rx_databuff, 0, sizeof(tp->Rx_databuff));

	return rtl8169_rx_fill(tp);
}