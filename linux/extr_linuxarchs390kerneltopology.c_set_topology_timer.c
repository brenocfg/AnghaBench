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

/* Variables and functions */
 int HZ ; 
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  topology_poll ; 
 int /*<<< orphan*/  topology_timer ; 

__attribute__((used)) static void set_topology_timer(void)
{
	if (atomic_add_unless(&topology_poll, -1, 0))
		mod_timer(&topology_timer, jiffies + HZ / 10);
	else
		mod_timer(&topology_timer, jiffies + HZ * 60);
}