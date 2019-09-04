#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smi_info {TYPE_2__* curr_msg; int /*<<< orphan*/  si_sm; TYPE_1__* handlers; TYPE_2__* waiting_msg; } ;
typedef  enum si_sm_result { ____Placeholder_si_sm_result } si_sm_result ;
struct TYPE_4__ {int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int (* start_transaction ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int NOTIFY_STOP_MASK ; 
 int SI_SM_CALL_WITHOUT_DELAY ; 
 int SI_SM_IDLE ; 
 int atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct smi_info*) ; 
 int /*<<< orphan*/  debug_timestamp (char*) ; 
 int /*<<< orphan*/  return_hosed_msg (struct smi_info*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xaction_notifier_list ; 

__attribute__((used)) static enum si_sm_result start_next_msg(struct smi_info *smi_info)
{
	int              rv;

	if (!smi_info->waiting_msg) {
		smi_info->curr_msg = NULL;
		rv = SI_SM_IDLE;
	} else {
		int err;

		smi_info->curr_msg = smi_info->waiting_msg;
		smi_info->waiting_msg = NULL;
		debug_timestamp("Start2");
		err = atomic_notifier_call_chain(&xaction_notifier_list,
				0, smi_info);
		if (err & NOTIFY_STOP_MASK) {
			rv = SI_SM_CALL_WITHOUT_DELAY;
			goto out;
		}
		err = smi_info->handlers->start_transaction(
			smi_info->si_sm,
			smi_info->curr_msg->data,
			smi_info->curr_msg->data_size);
		if (err)
			return_hosed_msg(smi_info, err);

		rv = SI_SM_CALL_WITHOUT_DELAY;
	}
out:
	return rv;
}