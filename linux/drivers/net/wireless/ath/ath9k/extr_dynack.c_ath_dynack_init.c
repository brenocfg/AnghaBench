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
struct ath_dynack {int ackto; int /*<<< orphan*/  nodes; int /*<<< orphan*/  qlock; } ;
struct ath_hw {TYPE_1__* hw; struct ath_dynack dynack; } ;
struct TYPE_4__ {int /*<<< orphan*/  features; } ;
struct TYPE_3__ {TYPE_2__* wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NL80211_FEATURE_ACKTO_ESTIMATION ; 
 int /*<<< orphan*/  memset (struct ath_dynack*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void ath_dynack_init(struct ath_hw *ah)
{
	struct ath_dynack *da = &ah->dynack;

	memset(da, 0, sizeof(struct ath_dynack));

	spin_lock_init(&da->qlock);
	INIT_LIST_HEAD(&da->nodes);
	/* ackto = slottime + sifs + air delay */
	da->ackto = 9 + 16 + 64;

	ah->hw->wiphy->features |= NL80211_FEATURE_ACKTO_ESTIMATION;
}