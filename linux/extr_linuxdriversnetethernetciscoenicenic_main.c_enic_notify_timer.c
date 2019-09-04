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
struct enic {int /*<<< orphan*/  notify_timer; } ;

/* Variables and functions */
 scalar_t__ ENIC_NOTIFY_TIMER_PERIOD ; 
 struct enic* enic ; 
 int /*<<< orphan*/  enic_notify_check (struct enic*) ; 
 struct enic* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_timer ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 

__attribute__((used)) static void enic_notify_timer(struct timer_list *t)
{
	struct enic *enic = from_timer(enic, t, notify_timer);

	enic_notify_check(enic);

	mod_timer(&enic->notify_timer,
		round_jiffies(jiffies + ENIC_NOTIFY_TIMER_PERIOD));
}