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
typedef  size_t u8 ;
struct il_priv {int /*<<< orphan*/  hw; int /*<<< orphan*/ * queue_stop_count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_wake_queue (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static inline void
_il_wake_queue(struct il_priv *il, u8 ac)
{
	if (atomic_dec_return(&il->queue_stop_count[ac]) <= 0)
		ieee80211_wake_queue(il->hw, ac);
}