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
struct ath10k_htt {int /*<<< orphan*/ * rx_ops; struct ath10k* ar; } ;
struct TYPE_4__ {scalar_t__ target_64bit; } ;
struct TYPE_3__ {scalar_t__ dev_type; } ;
struct ath10k {TYPE_2__ hw_params; TYPE_1__ bus_param; } ;

/* Variables and functions */
 scalar_t__ ATH10K_DEV_TYPE_HL ; 
 int /*<<< orphan*/  htt_rx_ops_32 ; 
 int /*<<< orphan*/  htt_rx_ops_64 ; 
 int /*<<< orphan*/  htt_rx_ops_hl ; 

void ath10k_htt_set_rx_ops(struct ath10k_htt *htt)
{
	struct ath10k *ar = htt->ar;

	if (ar->bus_param.dev_type == ATH10K_DEV_TYPE_HL)
		htt->rx_ops = &htt_rx_ops_hl;
	else if (ar->hw_params.target_64bit)
		htt->rx_ops = &htt_rx_ops_64;
	else
		htt->rx_ops = &htt_rx_ops_32;
}