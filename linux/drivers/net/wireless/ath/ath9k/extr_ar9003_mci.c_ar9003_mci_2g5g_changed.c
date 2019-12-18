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
struct ath9k_hw_mci {int update_2g5g; int is_2g; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */

__attribute__((used)) static void ar9003_mci_2g5g_changed(struct ath_hw *ah, bool is_2g)
{
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;

	if (!mci->update_2g5g &&
	    (mci->is_2g != is_2g))
		mci->update_2g5g = true;

	mci->is_2g = is_2g;
}