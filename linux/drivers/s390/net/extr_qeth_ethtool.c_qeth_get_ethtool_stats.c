#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {unsigned int no_out_queues; TYPE_1__** out_qs; } ;
struct qeth_card {TYPE_2__ qdio; int /*<<< orphan*/  stats; } ;
struct net_device {struct qeth_card* ml_priv; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_STATS_LEN ; 
 int /*<<< orphan*/  TXQ_STATS_LEN ; 
 int /*<<< orphan*/  card_stats ; 
 int /*<<< orphan*/  qeth_add_stat_data (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txq_stats ; 

__attribute__((used)) static void qeth_get_ethtool_stats(struct net_device *dev,
				   struct ethtool_stats *stats, u64 *data)
{
	struct qeth_card *card = dev->ml_priv;
	unsigned int i;

	qeth_add_stat_data(&data, &card->stats, card_stats, CARD_STATS_LEN);
	for (i = 0; i < card->qdio.no_out_queues; i++)
		qeth_add_stat_data(&data, &card->qdio.out_qs[i]->stats,
				   txq_stats, TXQ_STATS_LEN);
}