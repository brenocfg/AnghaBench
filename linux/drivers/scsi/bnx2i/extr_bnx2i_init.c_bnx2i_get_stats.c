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
struct iscsi_stats_info {scalar_t__ rxq_avg_depth; scalar_t__ txq_avg_depth; int /*<<< orphan*/  rxq_size; int /*<<< orphan*/  txq_size; int /*<<< orphan*/  max_frame_size; scalar_t__ mac_add1; int /*<<< orphan*/  version; } ;
struct bnx2i_hba {int /*<<< orphan*/  max_cqes; int /*<<< orphan*/  max_sqes; TYPE_2__* netdev; TYPE_1__* cnic; } ;
struct TYPE_4__ {int /*<<< orphan*/  mtu; } ;
struct TYPE_3__ {int /*<<< orphan*/  mac_addr; scalar_t__ stats_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_MODULE_VERSION ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GET_STATS_64 (struct bnx2i_hba*,struct iscsi_stats_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_bytes ; 
 int /*<<< orphan*/  rx_pdus ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tx_bytes ; 
 int /*<<< orphan*/  tx_pdus ; 

int bnx2i_get_stats(void *handle)
{
	struct bnx2i_hba *hba = handle;
	struct iscsi_stats_info *stats;

	if (!hba)
		return -EINVAL;

	stats = (struct iscsi_stats_info *)hba->cnic->stats_addr;

	if (!stats)
		return -ENOMEM;

	strlcpy(stats->version, DRV_MODULE_VERSION, sizeof(stats->version));
	memcpy(stats->mac_add1 + 2, hba->cnic->mac_addr, ETH_ALEN);

	stats->max_frame_size = hba->netdev->mtu;
	stats->txq_size = hba->max_sqes;
	stats->rxq_size = hba->max_cqes;

	stats->txq_avg_depth = 0;
	stats->rxq_avg_depth = 0;

	GET_STATS_64(hba, stats, rx_pdus);
	GET_STATS_64(hba, stats, rx_bytes);

	GET_STATS_64(hba, stats, tx_pdus);
	GET_STATS_64(hba, stats, tx_bytes);

	return 0;
}