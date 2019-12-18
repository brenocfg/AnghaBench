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
struct ath_hw_private_ops {int /*<<< orphan*/  is_aic_enabled; } ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar9003_hw_is_aic_enabled ; 
 struct ath_hw_private_ops* ath9k_hw_private_ops (struct ath_hw*) ; 

void ar9003_hw_attach_aic_ops(struct ath_hw *ah)
{
	struct ath_hw_private_ops *priv_ops = ath9k_hw_private_ops(ah);

	priv_ops->is_aic_enabled = ar9003_hw_is_aic_enabled;
}