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
struct rtl8169_private {unsigned int dirty_tx; unsigned int cur_tx; } ;

/* Variables and functions */
 unsigned int NUM_TX_DESC ; 

__attribute__((used)) static bool rtl_tx_slots_avail(struct rtl8169_private *tp,
			       unsigned int nr_frags)
{
	unsigned int slots_avail = tp->dirty_tx + NUM_TX_DESC - tp->cur_tx;

	/* A skbuff with nr_frags needs nr_frags+1 entries in the tx queue */
	return slots_avail > nr_frags;
}