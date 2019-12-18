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
struct mirror_set {int /*<<< orphan*/  timer_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mirror_set* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct mirror_set* ms ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  wakeup_mirrord (struct mirror_set*) ; 

__attribute__((used)) static void delayed_wake_fn(struct timer_list *t)
{
	struct mirror_set *ms = from_timer(ms, t, timer);

	clear_bit(0, &ms->timer_pending);
	wakeup_mirrord(ms);
}