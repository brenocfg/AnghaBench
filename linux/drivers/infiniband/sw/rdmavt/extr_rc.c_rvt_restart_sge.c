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
struct TYPE_2__ {int /*<<< orphan*/  num_sge; } ;
struct rvt_swqe {scalar_t__ length; TYPE_1__ wr; int /*<<< orphan*/ * sg_list; } ;
struct rvt_sge_state {scalar_t__ total_len; int /*<<< orphan*/  num_sge; int /*<<< orphan*/ * sg_list; int /*<<< orphan*/  sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  rvt_skip_sge (struct rvt_sge_state*,scalar_t__,int) ; 

u32 rvt_restart_sge(struct rvt_sge_state *ss, struct rvt_swqe *wqe, u32 len)
{
	ss->sge = wqe->sg_list[0];
	ss->sg_list = wqe->sg_list + 1;
	ss->num_sge = wqe->wr.num_sge;
	ss->total_len = wqe->length;
	rvt_skip_sge(ss, len, false);
	return wqe->length - len;
}