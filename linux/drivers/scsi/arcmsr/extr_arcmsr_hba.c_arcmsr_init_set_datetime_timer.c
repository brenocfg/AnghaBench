#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;
struct AdapterControlBlock {TYPE_1__ refresh_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  arcmsr_set_iop_datetime ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arcmsr_init_set_datetime_timer(struct AdapterControlBlock *pacb)
{
	timer_setup(&pacb->refresh_timer, arcmsr_set_iop_datetime, 0);
	pacb->refresh_timer.expires = jiffies + msecs_to_jiffies(60 * 1000);
	add_timer(&pacb->refresh_timer);
}