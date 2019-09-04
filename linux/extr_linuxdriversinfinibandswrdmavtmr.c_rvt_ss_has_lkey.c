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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  mr; } ;
struct rvt_sge_state {int num_sge; TYPE_2__* sg_list; TYPE_1__ sge; } ;
struct TYPE_4__ {int /*<<< orphan*/  mr; } ;

/* Variables and functions */
 int rvt_mr_has_lkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool rvt_ss_has_lkey(struct rvt_sge_state *ss, u32 lkey)
{
	int i;
	bool rval = false;

	if (!ss->num_sge)
		return rval;
	/* first one */
	rval = rvt_mr_has_lkey(ss->sge.mr, lkey);
	/* any others */
	for (i = 0; !rval && i < ss->num_sge - 1; i++)
		rval = rvt_mr_has_lkey(ss->sg_list[i].mr, lkey);
	return rval;
}