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
typedef  int /*<<< orphan*/  u8 ;
struct hnae3_knic_private_info {int /*<<< orphan*/  num_tqps; } ;
struct hnae3_handle {struct hnae3_knic_private_info kinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS3_RXQ_STATS_COUNT ; 
 int /*<<< orphan*/  HNS3_TXQ_STATS_COUNT ; 
 int /*<<< orphan*/  hns3_rxq_stats ; 
 int /*<<< orphan*/  hns3_txq_stats ; 
 int /*<<< orphan*/ * hns3_update_strings (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static u8 *hns3_get_strings_tqps(struct hnae3_handle *handle, u8 *data)
{
	struct hnae3_knic_private_info *kinfo = &handle->kinfo;
	const char tx_prefix[] = "txq";
	const char rx_prefix[] = "rxq";

	/* get strings for Tx */
	data = hns3_update_strings(data, hns3_txq_stats, HNS3_TXQ_STATS_COUNT,
				   kinfo->num_tqps, tx_prefix);

	/* get strings for Rx */
	data = hns3_update_strings(data, hns3_rxq_stats, HNS3_RXQ_STATS_COUNT,
				   kinfo->num_tqps, rx_prefix);

	return data;
}