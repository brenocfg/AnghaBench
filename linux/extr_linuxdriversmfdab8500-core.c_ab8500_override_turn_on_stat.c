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
typedef  void* u8 ;

/* Variables and functions */
 int /*<<< orphan*/  on_stat_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 void* turn_on_stat_mask ; 
 void* turn_on_stat_set ; 

void ab8500_override_turn_on_stat(u8 mask, u8 set)
{
	spin_lock(&on_stat_lock);
	turn_on_stat_mask = mask;
	turn_on_stat_set = set;
	spin_unlock(&on_stat_lock);
}