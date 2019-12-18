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
struct ieee80211_hw {struct ath10k* priv; } ;
struct TYPE_4__ {TYPE_1__* hw_ops; } ;
struct ath10k {TYPE_2__ hw_params; } ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_coverage_class ) (struct ath10k*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  stub1 (struct ath10k*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_mac_op_set_coverage_class(struct ieee80211_hw *hw, s16 value)
{
	struct ath10k *ar = hw->priv;

	/* This function should never be called if setting the coverage class
	 * is not supported on this hardware.
	 */
	if (!ar->hw_params.hw_ops->set_coverage_class) {
		WARN_ON_ONCE(1);
		return;
	}
	ar->hw_params.hw_ops->set_coverage_class(ar, value);
}