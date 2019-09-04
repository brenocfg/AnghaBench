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
struct tx_queue {int /*<<< orphan*/  index; } ;
struct mv643xx_eth_private {int t_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  TXQ_BW_CONF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXQ_BW_TOKENS (int /*<<< orphan*/ ) ; 
 struct mv643xx_eth_private* txq_to_mp (struct tx_queue*) ; 
 int /*<<< orphan*/  wrlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void txq_set_rate(struct tx_queue *txq, int rate, int burst)
{
	struct mv643xx_eth_private *mp = txq_to_mp(txq);
	int token_rate;
	int bucket_size;

	token_rate = ((rate / 1000) * 64) / (mp->t_clk / 1000);
	if (token_rate > 1023)
		token_rate = 1023;

	bucket_size = (burst + 255) >> 8;
	if (bucket_size > 65535)
		bucket_size = 65535;

	wrlp(mp, TXQ_BW_TOKENS(txq->index), token_rate << 14);
	wrlp(mp, TXQ_BW_CONF(txq->index), (bucket_size << 10) | token_rate);
}