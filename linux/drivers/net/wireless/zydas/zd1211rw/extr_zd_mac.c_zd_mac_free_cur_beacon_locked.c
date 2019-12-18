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
struct TYPE_4__ {int /*<<< orphan*/ * cur_beacon; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
struct zd_mac {TYPE_2__ beacon; TYPE_1__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zd_mac_free_cur_beacon_locked(struct zd_mac *mac)
{
	ZD_ASSERT(mutex_is_locked(&mac->chip.mutex));

	kfree_skb(mac->beacon.cur_beacon);
	mac->beacon.cur_beacon = NULL;
}