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
struct ieee80211_hw {struct ar9170* priv; } ;
struct ar9170 {int /*<<< orphan*/  tx_total_queued; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool carl9170_tx_frames_pending(struct ieee80211_hw *hw)
{
	struct ar9170 *ar = hw->priv;

	return !!atomic_read(&ar->tx_total_queued);
}