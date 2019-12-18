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
struct sk_buff {int dummy; } ;
struct ath10k_htt {TYPE_1__* tx_ops; } ;
typedef  enum ath10k_hw_txrx_mode { ____Placeholder_ath10k_hw_txrx_mode } ath10k_hw_txrx_mode ;
struct TYPE_2__ {int (* htt_tx ) (struct ath10k_htt*,int,struct sk_buff*) ;} ;

/* Variables and functions */
 int stub1 (struct ath10k_htt*,int,struct sk_buff*) ; 

__attribute__((used)) static inline int ath10k_htt_tx(struct ath10k_htt *htt,
				enum ath10k_hw_txrx_mode txmode,
				struct sk_buff *msdu)
{
	return htt->tx_ops->htt_tx(htt, txmode, msdu);
}