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
struct hinic_ceqs {struct hinic_ceq_cb* ceq_cb; } ;
struct hinic_ceq_cb {int ceqe_state; int /*<<< orphan*/ * handler; } ;
typedef  enum hinic_ceq_type { ____Placeholder_hinic_ceq_type } hinic_ceq_type ;

/* Variables and functions */
 int HINIC_EQE_ENABLED ; 
 int HINIC_EQE_RUNNING ; 
 int /*<<< orphan*/  schedule () ; 

void hinic_ceq_unregister_cb(struct hinic_ceqs *ceqs,
			     enum hinic_ceq_type event)
{
	struct hinic_ceq_cb *ceq_cb = &ceqs->ceq_cb[event];

	ceq_cb->ceqe_state &= ~HINIC_EQE_ENABLED;

	while (ceq_cb->ceqe_state & HINIC_EQE_RUNNING)
		schedule();

	ceq_cb->handler = NULL;
}