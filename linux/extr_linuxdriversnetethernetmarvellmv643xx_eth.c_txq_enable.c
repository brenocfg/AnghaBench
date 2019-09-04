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
struct tx_queue {int index; } ;
struct mv643xx_eth_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TXQ_COMMAND ; 
 struct mv643xx_eth_private* txq_to_mp (struct tx_queue*) ; 
 int /*<<< orphan*/  wrlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void txq_enable(struct tx_queue *txq)
{
	struct mv643xx_eth_private *mp = txq_to_mp(txq);
	wrlp(mp, TXQ_COMMAND, 1 << txq->index);
}