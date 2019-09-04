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
struct xgbe_prv_data {int /*<<< orphan*/  service_timer; int /*<<< orphan*/  service_work; int /*<<< orphan*/  dev_workqueue; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 struct xgbe_prv_data* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct xgbe_prv_data* pdata ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  service_timer ; 

__attribute__((used)) static void xgbe_service_timer(struct timer_list *t)
{
	struct xgbe_prv_data *pdata = from_timer(pdata, t, service_timer);

	queue_work(pdata->dev_workqueue, &pdata->service_work);

	mod_timer(&pdata->service_timer, jiffies + HZ);
}