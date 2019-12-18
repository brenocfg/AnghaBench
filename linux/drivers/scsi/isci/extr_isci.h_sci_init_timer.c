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
struct sci_timer {int /*<<< orphan*/  timer; scalar_t__ cancel; } ;

/* Variables and functions */
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,void (*) (struct timer_list*),int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void sci_init_timer(struct sci_timer *tmr, void (*fn)(struct timer_list *t))
{
	tmr->cancel = 0;
	timer_setup(&tmr->timer, fn, 0);
}