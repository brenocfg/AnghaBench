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
struct hns_nic_priv {int /*<<< orphan*/  service_task; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_STATE_DOWN ; 
 int /*<<< orphan*/  NIC_STATE_REMOVING ; 
 int /*<<< orphan*/  NIC_STATE_SERVICE_SCHED ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_nic_task_schedule(struct hns_nic_priv *priv)
{
	if (!test_bit(NIC_STATE_DOWN, &priv->state) &&
	    !test_bit(NIC_STATE_REMOVING, &priv->state) &&
	    !test_and_set_bit(NIC_STATE_SERVICE_SCHED, &priv->state))
		(void)schedule_work(&priv->service_task);
}