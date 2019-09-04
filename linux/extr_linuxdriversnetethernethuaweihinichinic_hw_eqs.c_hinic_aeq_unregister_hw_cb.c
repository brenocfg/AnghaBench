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
struct hinic_hw_event_cb {int hwe_state; int /*<<< orphan*/ * hwe_handler; } ;
struct hinic_aeqs {struct hinic_hw_event_cb* hwe_cb; } ;
typedef  enum hinic_aeq_type { ____Placeholder_hinic_aeq_type } hinic_aeq_type ;

/* Variables and functions */
 int HINIC_EQE_ENABLED ; 
 int HINIC_EQE_RUNNING ; 
 int /*<<< orphan*/  schedule () ; 

void hinic_aeq_unregister_hw_cb(struct hinic_aeqs *aeqs,
				enum hinic_aeq_type event)
{
	struct hinic_hw_event_cb *hwe_cb = &aeqs->hwe_cb[event];

	hwe_cb->hwe_state &= ~HINIC_EQE_ENABLED;

	while (hwe_cb->hwe_state & HINIC_EQE_RUNNING)
		schedule();

	hwe_cb->hwe_handler = NULL;
}