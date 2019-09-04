#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__* p_completion_word; } ;
struct qed_hwfn {TYPE_1__ dmae_info; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 scalar_t__ DMAE_COMPLETION_VAL ; 
 int /*<<< orphan*/  DMAE_MIN_WAIT_TIME ; 
 int /*<<< orphan*/  DP_NOTICE (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int EBUSY ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_dmae_operation_wait(struct qed_hwfn *p_hwfn)
{
	u32 wait_cnt_limit = 10000, wait_cnt = 0;
	int qed_status = 0;

	barrier();
	while (*p_hwfn->dmae_info.p_completion_word != DMAE_COMPLETION_VAL) {
		udelay(DMAE_MIN_WAIT_TIME);
		if (++wait_cnt > wait_cnt_limit) {
			DP_NOTICE(p_hwfn->cdev,
				  "Timed-out waiting for operation to complete. Completion word is 0x%08x expected 0x%08x.\n",
				  *p_hwfn->dmae_info.p_completion_word,
				 DMAE_COMPLETION_VAL);
			qed_status = -EBUSY;
			break;
		}

		/* to sync the completion_word since we are not
		 * using the volatile keyword for p_completion_word
		 */
		barrier();
	}

	if (qed_status == 0)
		*p_hwfn->dmae_info.p_completion_word = 0;

	return qed_status;
}