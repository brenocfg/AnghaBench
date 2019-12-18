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
struct TYPE_3__ {int info0; } ;
struct TYPE_4__ {TYPE_1__ common; } ;
struct htt_rx_desc {TYPE_2__ msdu_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_MSDU_END_INFO0_MSDU_LIMIT_ERR ; 
 int __cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ath10k_qca99x0_rx_desc_msdu_limit_error(struct htt_rx_desc *rxd)
{
	return !!(rxd->msdu_end.common.info0 &
		  __cpu_to_le32(RX_MSDU_END_INFO0_MSDU_LIMIT_ERR));
}