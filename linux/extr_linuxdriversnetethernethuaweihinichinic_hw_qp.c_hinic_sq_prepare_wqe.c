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
typedef  int /*<<< orphan*/  u16 ;
struct hinic_sq_wqe {TYPE_1__* buf_descs; int /*<<< orphan*/  task; int /*<<< orphan*/  ctrl; } ;
struct hinic_sq {int dummy; } ;
struct hinic_sge {int dummy; } ;
struct TYPE_2__ {struct hinic_sge sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  sq_prepare_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sq_prepare_task (int /*<<< orphan*/ *) ; 

void hinic_sq_prepare_wqe(struct hinic_sq *sq, u16 prod_idx,
			  struct hinic_sq_wqe *sq_wqe, struct hinic_sge *sges,
			  int nr_sges)
{
	int i;

	sq_prepare_ctrl(&sq_wqe->ctrl, prod_idx, nr_sges);

	sq_prepare_task(&sq_wqe->task);

	for (i = 0; i < nr_sges; i++)
		sq_wqe->buf_descs[i].sge = sges[i];
}