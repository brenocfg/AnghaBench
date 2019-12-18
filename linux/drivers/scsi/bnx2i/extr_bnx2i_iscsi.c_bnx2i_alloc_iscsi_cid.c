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
typedef  int u32 ;
struct TYPE_2__ {int cid_q_cons_idx; int cid_q_max_idx; int* cid_que; int /*<<< orphan*/  cid_free_cnt; } ;
struct bnx2i_hba {TYPE_1__ cid_que; } ;

/* Variables and functions */

__attribute__((used)) static u32 bnx2i_alloc_iscsi_cid(struct bnx2i_hba *hba)
{
	int idx;

	if (!hba->cid_que.cid_free_cnt)
		return -1;

	idx = hba->cid_que.cid_q_cons_idx;
	hba->cid_que.cid_q_cons_idx++;
	if (hba->cid_que.cid_q_cons_idx == hba->cid_que.cid_q_max_idx)
		hba->cid_que.cid_q_cons_idx = 0;

	hba->cid_que.cid_free_cnt--;
	return hba->cid_que.cid_que[idx];
}