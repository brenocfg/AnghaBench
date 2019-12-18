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
struct aq_nic_s {int /*<<< orphan*/  service_task; int /*<<< orphan*/  service_timer; } ;

/* Variables and functions */
 scalar_t__ AQ_CFG_SERVICE_TIMER_INTERVAL ; 
 int /*<<< orphan*/  aq_ndev_schedule_work (int /*<<< orphan*/ *) ; 
 struct aq_nic_s* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct aq_nic_s* self ; 
 int /*<<< orphan*/  service_timer ; 

__attribute__((used)) static void aq_nic_service_timer_cb(struct timer_list *t)
{
	struct aq_nic_s *self = from_timer(self, t, service_timer);

	mod_timer(&self->service_timer, jiffies + AQ_CFG_SERVICE_TIMER_INTERVAL);

	aq_ndev_schedule_work(&self->service_task);
}