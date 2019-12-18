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
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
struct qed_ptt {TYPE_2__ pxp; } ;
struct qed_hwfn {TYPE_1__* p_ptt_pool; } ;
struct TYPE_3__ {struct qed_ptt* ptts; } ;

/* Variables and functions */
 int PXP_EXTERNAL_BAR_PF_WINDOW_NUM ; 
 int /*<<< orphan*/  QED_BAR_INVALID_OFFSET ; 

void qed_ptt_invalidate(struct qed_hwfn *p_hwfn)
{
	struct qed_ptt *p_ptt;
	int i;

	for (i = 0; i < PXP_EXTERNAL_BAR_PF_WINDOW_NUM; i++) {
		p_ptt = &p_hwfn->p_ptt_pool->ptts[i];
		p_ptt->pxp.offset = QED_BAR_INVALID_OFFSET;
	}
}