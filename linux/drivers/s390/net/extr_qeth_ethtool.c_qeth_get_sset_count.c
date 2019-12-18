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
struct TYPE_2__ {int no_out_queues; } ;
struct qeth_card {TYPE_1__ qdio; } ;
struct net_device {struct qeth_card* ml_priv; } ;

/* Variables and functions */
 int CARD_STATS_LEN ; 
 int EINVAL ; 
#define  ETH_SS_STATS 128 
 int TXQ_STATS_LEN ; 

__attribute__((used)) static int qeth_get_sset_count(struct net_device *dev, int stringset)
{
	struct qeth_card *card = dev->ml_priv;

	switch (stringset) {
	case ETH_SS_STATS:
		return CARD_STATS_LEN +
		       card->qdio.no_out_queues * TXQ_STATS_LEN;
	default:
		return -EINVAL;
	}
}