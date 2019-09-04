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

/* Variables and functions */
 scalar_t__ SPUSCHED_TICK ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spusched_task ; 
 int /*<<< orphan*/  spusched_timer ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spusched_wake(struct timer_list *unused)
{
	mod_timer(&spusched_timer, jiffies + SPUSCHED_TICK);
	wake_up_process(spusched_task);
}