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
struct delay_c {int /*<<< orphan*/  flush_expired_bios; int /*<<< orphan*/  kdelayd_wq; } ;

/* Variables and functions */
 struct delay_c* dc ; 
 int /*<<< orphan*/  delay_timer ; 
 struct delay_c* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_delayed_timer(struct timer_list *t)
{
	struct delay_c *dc = from_timer(dc, t, delay_timer);

	queue_work(dc->kdelayd_wq, &dc->flush_expired_bios);
}