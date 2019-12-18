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
struct timer_list {scalar_t__ expires; } ;
struct megasas_instance {struct timer_list sriov_heartbeat_timer; } ;

/* Variables and functions */
 scalar_t__ MEGASAS_SRIOV_HEARTBEAT_INTERVAL_VF ; 
 int /*<<< orphan*/  add_timer (struct timer_list*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  megasas_sriov_heartbeat_handler ; 
 int /*<<< orphan*/  timer_setup (struct timer_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void megasas_start_timer(struct megasas_instance *instance)
{
	struct timer_list *timer = &instance->sriov_heartbeat_timer;

	timer_setup(timer, megasas_sriov_heartbeat_handler, 0);
	timer->expires = jiffies + MEGASAS_SRIOV_HEARTBEAT_INTERVAL_VF;
	add_timer(timer);
}