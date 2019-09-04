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
struct timer_list {int dummy; } ;
struct mv643xx_eth_private {int /*<<< orphan*/  mib_counters_timer; } ;

/* Variables and functions */
 int HZ ; 
 struct mv643xx_eth_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mib_counters_timer ; 
 int /*<<< orphan*/  mib_counters_update (struct mv643xx_eth_private*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct mv643xx_eth_private* mp ; 

__attribute__((used)) static void mib_counters_timer_wrapper(struct timer_list *t)
{
	struct mv643xx_eth_private *mp = from_timer(mp, t, mib_counters_timer);
	mib_counters_update(mp);
	mod_timer(&mp->mib_counters_timer, jiffies + 30 * HZ);
}