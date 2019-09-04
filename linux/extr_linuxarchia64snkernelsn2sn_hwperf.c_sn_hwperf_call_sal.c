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
typedef  int /*<<< orphan*/  u64 ;
struct sn_hwperf_op_info {int ret; int /*<<< orphan*/  v0; scalar_t__ p; TYPE_1__* a; int /*<<< orphan*/  op; } ;
struct TYPE_2__ {int /*<<< orphan*/  sz; int /*<<< orphan*/  arg; } ;

/* Variables and functions */
 int ia64_sn_hwperf_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sn_hwperf_master_nasid ; 

__attribute__((used)) static void sn_hwperf_call_sal(void *info)
{
	struct sn_hwperf_op_info *op_info = info;
	int r;

	r = ia64_sn_hwperf_op(sn_hwperf_master_nasid, op_info->op,
		      op_info->a->arg, op_info->a->sz,
		      (u64) op_info->p, 0, 0, op_info->v0);
	op_info->ret = r;
}