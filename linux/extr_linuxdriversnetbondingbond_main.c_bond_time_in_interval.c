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
struct TYPE_2__ {int /*<<< orphan*/  arp_interval; } ;
struct bonding {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int time_in_range (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static bool bond_time_in_interval(struct bonding *bond, unsigned long last_act,
				  int mod)
{
	int delta_in_ticks = msecs_to_jiffies(bond->params.arp_interval);

	return time_in_range(jiffies,
			     last_act - delta_in_ticks,
			     last_act + mod * delta_in_ticks + delta_in_ticks/2);
}