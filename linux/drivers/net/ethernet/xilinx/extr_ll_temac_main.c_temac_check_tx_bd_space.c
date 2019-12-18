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
struct temac_local {int tx_bd_tail; struct cdmac_bd* tx_bd_v; } ;
struct cdmac_bd {scalar_t__ app0; } ;

/* Variables and functions */
 int NETDEV_TX_BUSY ; 
 int TX_BD_NUM ; 

__attribute__((used)) static inline int temac_check_tx_bd_space(struct temac_local *lp, int num_frag)
{
	struct cdmac_bd *cur_p;
	int tail;

	tail = lp->tx_bd_tail;
	cur_p = &lp->tx_bd_v[tail];

	do {
		if (cur_p->app0)
			return NETDEV_TX_BUSY;

		tail++;
		if (tail >= TX_BD_NUM)
			tail = 0;

		cur_p = &lp->tx_bd_v[tail];
		num_frag--;
	} while (num_frag >= 0);

	return 0;
}