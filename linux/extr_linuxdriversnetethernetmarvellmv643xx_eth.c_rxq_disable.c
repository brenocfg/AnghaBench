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
struct rx_queue {int index; } ;
struct mv643xx_eth_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXQ_COMMAND ; 
 int rdlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 
 struct mv643xx_eth_private* rxq_to_mp (struct rx_queue*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wrlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rxq_disable(struct rx_queue *rxq)
{
	struct mv643xx_eth_private *mp = rxq_to_mp(rxq);
	u8 mask = 1 << rxq->index;

	wrlp(mp, RXQ_COMMAND, mask << 8);
	while (rdlp(mp, RXQ_COMMAND) & mask)
		udelay(10);
}