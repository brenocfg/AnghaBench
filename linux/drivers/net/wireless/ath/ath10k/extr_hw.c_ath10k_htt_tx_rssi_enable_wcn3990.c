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
struct TYPE_2__ {int flags2; } ;
struct htt_resp {TYPE_1__ data_tx_completion; } ;

/* Variables and functions */
 int HTT_TX_DATA_RSSI_ENABLE_WCN3990 ; 

__attribute__((used)) static int ath10k_htt_tx_rssi_enable_wcn3990(struct htt_resp *resp)
{
	return (resp->data_tx_completion.flags2 &
		HTT_TX_DATA_RSSI_ENABLE_WCN3990);
}