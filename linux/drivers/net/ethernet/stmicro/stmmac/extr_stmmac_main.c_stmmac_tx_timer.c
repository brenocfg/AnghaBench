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
struct timer_list {int dummy; } ;
struct stmmac_tx_queue {size_t queue_index; int /*<<< orphan*/  txtimer; struct stmmac_priv* priv_data; } ;
struct stmmac_priv {struct stmmac_channel* channel; } ;
struct stmmac_channel {int /*<<< orphan*/  tx_napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMMAC_COAL_TIMER (int) ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 struct stmmac_tx_queue* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct stmmac_tx_queue* tx_q ; 
 int /*<<< orphan*/  txtimer ; 

__attribute__((used)) static void stmmac_tx_timer(struct timer_list *t)
{
	struct stmmac_tx_queue *tx_q = from_timer(tx_q, t, txtimer);
	struct stmmac_priv *priv = tx_q->priv_data;
	struct stmmac_channel *ch;

	ch = &priv->channel[tx_q->queue_index];

	/*
	 * If NAPI is already running we can miss some events. Let's rearm
	 * the timer and try again.
	 */
	if (likely(napi_schedule_prep(&ch->tx_napi)))
		__napi_schedule(&ch->tx_napi);
	else
		mod_timer(&tx_q->txtimer, STMMAC_COAL_TIMER(10));
}