#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tx_queue {int index; } ;
struct mv643xx_eth_private {TYPE_1__* shared; } ;
struct TYPE_2__ {int tx_bw_control; } ;

/* Variables and functions */
 int TXQ_FIX_PRIO_CONF ; 
 int TXQ_FIX_PRIO_CONF_MOVED ; 
#define  TX_BW_CONTROL_NEW_LAYOUT 129 
#define  TX_BW_CONTROL_OLD_LAYOUT 128 
 int rdlp (struct mv643xx_eth_private*,int) ; 
 struct mv643xx_eth_private* txq_to_mp (struct tx_queue*) ; 
 int /*<<< orphan*/  wrlp (struct mv643xx_eth_private*,int,int) ; 

__attribute__((used)) static void txq_set_fixed_prio_mode(struct tx_queue *txq)
{
	struct mv643xx_eth_private *mp = txq_to_mp(txq);
	int off;
	u32 val;

	/*
	 * Turn on fixed priority mode.
	 */
	off = 0;
	switch (mp->shared->tx_bw_control) {
	case TX_BW_CONTROL_OLD_LAYOUT:
		off = TXQ_FIX_PRIO_CONF;
		break;
	case TX_BW_CONTROL_NEW_LAYOUT:
		off = TXQ_FIX_PRIO_CONF_MOVED;
		break;
	}

	if (off) {
		val = rdlp(mp, off);
		val |= 1 << txq->index;
		wrlp(mp, off, val);
	}
}