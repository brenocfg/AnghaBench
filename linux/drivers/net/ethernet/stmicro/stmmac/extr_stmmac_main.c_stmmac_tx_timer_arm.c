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
typedef  size_t u32 ;
struct stmmac_tx_queue {int /*<<< orphan*/  txtimer; } ;
struct stmmac_priv {int /*<<< orphan*/  tx_coal_timer; struct stmmac_tx_queue* tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMMAC_COAL_TIMER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmmac_tx_timer_arm(struct stmmac_priv *priv, u32 queue)
{
	struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];

	mod_timer(&tx_q->txtimer, STMMAC_COAL_TIMER(priv->tx_coal_timer));
}