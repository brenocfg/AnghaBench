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
typedef  int /*<<< orphan*/  u64 ;
struct hclge_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_OPC_QUERY_PFC_TX_PKT_CNT ; 
 int hclge_pfc_stats_get (struct hclge_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hclge_pfc_tx_stats_get(struct hclge_dev *hdev, u64 *stats)
{
	return hclge_pfc_stats_get(hdev, HCLGE_OPC_QUERY_PFC_TX_PKT_CNT, stats);
}