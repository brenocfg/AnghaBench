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
typedef  size_t u16 ;
struct nvmet_sq {size_t qid; size_t size; scalar_t__ sqhd; } ;
struct nvmet_ctrl {struct nvmet_sq** sqs; } ;

/* Variables and functions */

void nvmet_sq_setup(struct nvmet_ctrl *ctrl, struct nvmet_sq *sq,
		u16 qid, u16 size)
{
	sq->sqhd = 0;
	sq->qid = qid;
	sq->size = size;

	ctrl->sqs[qid] = sq;
}