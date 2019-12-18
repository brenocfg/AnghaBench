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
struct amd8111e_priv {int tx_idx; scalar_t__* tx_skbuff; } ;

/* Variables and functions */
 int TX_BUFF_MOD_MASK ; 

__attribute__((used)) static int amd8111e_tx_queue_avail(struct amd8111e_priv *lp)
{
	int tx_index = lp->tx_idx & TX_BUFF_MOD_MASK;
	if (lp->tx_skbuff[tx_index])
		return -1;
	else
		return 0;

}