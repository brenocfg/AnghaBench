#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t uint32_t ;
struct scsi_qla_host {int /*<<< orphan*/  iocb_cnt; struct mrb** active_mrb_array; } ;
struct mrb {scalar_t__ iocb_cnt; } ;

/* Variables and functions */
 size_t MAX_MRB ; 

__attribute__((used)) static struct mrb *qla4xxx_del_mrb_from_active_array(struct scsi_qla_host *ha,
						     uint32_t index)
{
	struct mrb *mrb = NULL;

	/* validate handle and remove from active array */
	if (index >= MAX_MRB)
		return mrb;

	mrb = ha->active_mrb_array[index];
	ha->active_mrb_array[index] = NULL;
	if (!mrb)
		return mrb;

	/* update counters */
	ha->iocb_cnt -= mrb->iocb_cnt;

	return mrb;
}