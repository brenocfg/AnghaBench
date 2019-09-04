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
struct qed_hwfn {TYPE_1__* p_spq; } ;
struct TYPE_2__ {int cid; } ;

/* Variables and functions */

u32 qed_spq_get_cid(struct qed_hwfn *p_hwfn)
{
	if (!p_hwfn->p_spq)
		return 0xffffffff;      /* illegal */
	return p_hwfn->p_spq->cid;
}