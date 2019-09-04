#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ expires; } ;

/* Variables and functions */
 scalar_t__ CPEI_INTERVAL ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 TYPE_1__ sn_cpei_timer ; 
 int /*<<< orphan*/  sn_cpei_timer_handler ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sn_init_cpei_timer(void)
{
	timer_setup(&sn_cpei_timer, sn_cpei_timer_handler, 0);
	sn_cpei_timer.expires = jiffies + CPEI_INTERVAL;
	add_timer(&sn_cpei_timer);
}