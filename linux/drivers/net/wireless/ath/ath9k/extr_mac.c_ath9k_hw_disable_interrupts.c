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

/* Variables and functions */
 int ATH9K_INT_GLOBAL ; 
 int /*<<< orphan*/  ath9k_hw_kill_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

void ath9k_hw_disable_interrupts(struct ath_hw *ah)
{
	if (!(ah->imask & ATH9K_INT_GLOBAL))
		atomic_set(&ah->intr_ref_cnt, -1);
	else
		atomic_dec(&ah->intr_ref_cnt);

	ath9k_hw_kill_interrupts(ah);
}