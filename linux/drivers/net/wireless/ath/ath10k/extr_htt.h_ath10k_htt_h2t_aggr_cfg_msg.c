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
typedef  int /*<<< orphan*/  u8 ;
struct ath10k_htt {TYPE_1__* tx_ops; } ;
struct TYPE_2__ {int (* htt_h2t_aggr_cfg_msg ) (struct ath10k_htt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct ath10k_htt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ath10k_htt_h2t_aggr_cfg_msg(struct ath10k_htt *htt,
					      u8 max_subfrms_ampdu,
					      u8 max_subfrms_amsdu)

{
	if (!htt->tx_ops->htt_h2t_aggr_cfg_msg)
		return -EOPNOTSUPP;

	return htt->tx_ops->htt_h2t_aggr_cfg_msg(htt,
						 max_subfrms_ampdu,
						 max_subfrms_amsdu);
}