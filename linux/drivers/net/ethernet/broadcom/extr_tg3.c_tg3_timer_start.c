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
struct TYPE_2__ {scalar_t__ expires; } ;
struct tg3 {TYPE_1__ timer; scalar_t__ timer_offset; int /*<<< orphan*/  timer_multiplier; int /*<<< orphan*/  timer_counter; int /*<<< orphan*/  asf_multiplier; int /*<<< orphan*/  asf_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void tg3_timer_start(struct tg3 *tp)
{
	tp->asf_counter   = tp->asf_multiplier;
	tp->timer_counter = tp->timer_multiplier;

	tp->timer.expires = jiffies + tp->timer_offset;
	add_timer(&tp->timer);
}