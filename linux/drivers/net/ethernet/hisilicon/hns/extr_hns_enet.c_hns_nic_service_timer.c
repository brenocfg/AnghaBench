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
struct hns_nic_priv {int /*<<< orphan*/  service_timer; } ;

/* Variables and functions */
 scalar_t__ SERVICE_TIMER_HZ ; 
 struct hns_nic_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_nic_task_schedule (struct hns_nic_priv*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct hns_nic_priv* priv ; 
 int /*<<< orphan*/  service_timer ; 

__attribute__((used)) static void hns_nic_service_timer(struct timer_list *t)
{
	struct hns_nic_priv *priv = from_timer(priv, t, service_timer);

	(void)mod_timer(&priv->service_timer, jiffies + SERVICE_TIMER_HZ);

	hns_nic_task_schedule(priv);
}