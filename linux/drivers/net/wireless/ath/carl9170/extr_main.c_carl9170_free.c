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
struct ar9170 {int /*<<< orphan*/  hw; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * survey; int /*<<< orphan*/ * mem_bitmap; int /*<<< orphan*/ * rx_failover; int /*<<< orphan*/  registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_INITIALIZED (struct ar9170*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void carl9170_free(struct ar9170 *ar)
{
	WARN_ON(ar->registered);
	WARN_ON(IS_INITIALIZED(ar));

	kfree_skb(ar->rx_failover);
	ar->rx_failover = NULL;

	kfree(ar->mem_bitmap);
	ar->mem_bitmap = NULL;

	kfree(ar->survey);
	ar->survey = NULL;

	mutex_destroy(&ar->mutex);

	ieee80211_free_hw(ar->hw);
}