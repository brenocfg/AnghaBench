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
struct qed_ptt {int dummy; } ;
struct qed_hwfn {TYPE_1__* p_ptt_pool; } ;
typedef  enum reserved_ptts { ____Placeholder_reserved_ptts } reserved_ptts ;
struct TYPE_2__ {struct qed_ptt* ptts; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int) ; 
 int RESERVED_PTT_MAX ; 

struct qed_ptt *qed_get_reserved_ptt(struct qed_hwfn *p_hwfn,
				     enum reserved_ptts ptt_idx)
{
	if (ptt_idx >= RESERVED_PTT_MAX) {
		DP_NOTICE(p_hwfn,
			  "Requested PTT %d is out of range\n", ptt_idx);
		return NULL;
	}

	return &p_hwfn->p_ptt_pool->ptts[ptt_idx];
}