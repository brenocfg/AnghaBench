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
struct ag71xx {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 struct ag71xx* ag ; 
 struct ag71xx* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oom_timer ; 

__attribute__((used)) static void ag71xx_oom_timer_handler(struct timer_list *t)
{
	struct ag71xx *ag = from_timer(ag, t, oom_timer);

	napi_schedule(&ag->napi);
}