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
struct TYPE_4__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  idx; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  idx; } ;
struct i40iw_qp_mr {TYPE_2__ rq_pbl; TYPE_1__ sq_pbl; int /*<<< orphan*/  shadow; int /*<<< orphan*/  sq_page; } ;
struct i40iw_qp_init_info {int virtual_map; int /*<<< orphan*/  rq_pa; int /*<<< orphan*/  sq_pa; int /*<<< orphan*/  shadow_area_pa; } ;
struct i40iw_pbl {scalar_t__ pbl_allocated; struct i40iw_qp_mr qp_mr; } ;
struct i40iw_qp {int /*<<< orphan*/  page; struct i40iw_pbl iwpbl; } ;
struct i40iw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40iw_setup_virt_qp(struct i40iw_device *iwdev,
			       struct i40iw_qp *iwqp,
			       struct i40iw_qp_init_info *init_info)
{
	struct i40iw_pbl *iwpbl = &iwqp->iwpbl;
	struct i40iw_qp_mr *qpmr = &iwpbl->qp_mr;

	iwqp->page = qpmr->sq_page;
	init_info->shadow_area_pa = cpu_to_le64(qpmr->shadow);
	if (iwpbl->pbl_allocated) {
		init_info->virtual_map = true;
		init_info->sq_pa = qpmr->sq_pbl.idx;
		init_info->rq_pa = qpmr->rq_pbl.idx;
	} else {
		init_info->sq_pa = qpmr->sq_pbl.addr;
		init_info->rq_pa = qpmr->rq_pbl.addr;
	}
	return 0;
}