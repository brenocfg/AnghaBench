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
struct ath10k_ce_pipe {int /*<<< orphan*/ * ops; } ;
struct ath10k {int hw_rev; } ;

/* Variables and functions */
#define  ATH10K_HW_WCN3990 128 
 int /*<<< orphan*/  ce_64_ops ; 
 int /*<<< orphan*/  ce_ops ; 

__attribute__((used)) static void ath10k_ce_set_ops(struct ath10k *ar,
			      struct ath10k_ce_pipe *ce_state)
{
	switch (ar->hw_rev) {
	case ATH10K_HW_WCN3990:
		ce_state->ops = &ce_64_ops;
		break;
	default:
		ce_state->ops = &ce_ops;
		break;
	}
}