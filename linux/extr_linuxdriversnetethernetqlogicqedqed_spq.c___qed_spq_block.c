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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ cookie; } ;
struct qed_spq_entry {TYPE_1__ comp_cb; } ;
struct qed_spq_comp_done {int /*<<< orphan*/  fw_return_code; int /*<<< orphan*/  done; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SPQ_BLOCK_DELAY_MAX_ITER ; 
 int /*<<< orphan*/  SPQ_BLOCK_DELAY_US ; 
 int /*<<< orphan*/  SPQ_BLOCK_SLEEP_MAX_ITER ; 
 int /*<<< orphan*/  SPQ_BLOCK_SLEEP_MS ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __qed_spq_block(struct qed_hwfn *p_hwfn,
			   struct qed_spq_entry *p_ent,
			   u8 *p_fw_ret, bool sleep_between_iter)
{
	struct qed_spq_comp_done *comp_done;
	u32 iter_cnt;

	comp_done = (struct qed_spq_comp_done *)p_ent->comp_cb.cookie;
	iter_cnt = sleep_between_iter ? SPQ_BLOCK_SLEEP_MAX_ITER
				      : SPQ_BLOCK_DELAY_MAX_ITER;

	while (iter_cnt--) {
		/* Validate we receive completion update */
		if (smp_load_acquire(&comp_done->done) == 1) { /* ^^^ */
			if (p_fw_ret)
				*p_fw_ret = comp_done->fw_return_code;
			return 0;
		}

		if (sleep_between_iter)
			msleep(SPQ_BLOCK_SLEEP_MS);
		else
			udelay(SPQ_BLOCK_DELAY_US);
	}

	return -EBUSY;
}