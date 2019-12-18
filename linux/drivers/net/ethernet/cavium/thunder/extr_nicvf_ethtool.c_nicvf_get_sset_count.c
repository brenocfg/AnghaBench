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
struct nicvf {int sqs_count; TYPE_1__* qs; struct nicvf** snicvf; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int rq_cnt; int sq_cnt; } ;

/* Variables and functions */
 int BGX_RX_STATS_COUNT ; 
 int BGX_TX_STATS_COUNT ; 
 int EINVAL ; 
 int ETH_SS_STATS ; 
 struct nicvf* netdev_priv (struct net_device*) ; 
 int nicvf_n_drv_stats ; 
 int nicvf_n_hw_stats ; 
 int nicvf_n_queue_stats ; 

__attribute__((used)) static int nicvf_get_sset_count(struct net_device *netdev, int sset)
{
	struct nicvf *nic = netdev_priv(netdev);
	int qstats_count;
	int sqs;

	if (sset != ETH_SS_STATS)
		return -EINVAL;

	qstats_count = nicvf_n_queue_stats *
		       (nic->qs->rq_cnt + nic->qs->sq_cnt);
	for (sqs = 0; sqs < nic->sqs_count; sqs++) {
		struct nicvf *snic;

		snic = nic->snicvf[sqs];
		if (!snic)
			continue;
		qstats_count += nicvf_n_queue_stats *
				(snic->qs->rq_cnt + snic->qs->sq_cnt);
	}

	return nicvf_n_hw_stats + nicvf_n_drv_stats +
		qstats_count +
		BGX_RX_STATS_COUNT + BGX_TX_STATS_COUNT;
}