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
struct ath_hw {int imask; int /*<<< orphan*/  intr_ref_cnt; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int ATH9K_INT_GLOBAL ; 
 int /*<<< orphan*/  INTERRUPT ; 
 int /*<<< orphan*/  __ath9k_hw_enable_interrupts (struct ath_hw*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

void ath9k_hw_enable_interrupts(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);

	if (!(ah->imask & ATH9K_INT_GLOBAL))
		return;

	if (!atomic_inc_and_test(&ah->intr_ref_cnt)) {
		ath_dbg(common, INTERRUPT, "Do not enable IER ref count %d\n",
			atomic_read(&ah->intr_ref_cnt));
		return;
	}

	__ath9k_hw_enable_interrupts(ah);
}