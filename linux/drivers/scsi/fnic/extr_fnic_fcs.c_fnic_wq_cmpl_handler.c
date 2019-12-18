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
struct fnic {unsigned int raw_wq_count; unsigned int rq_count; int /*<<< orphan*/ * cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  fnic_wq_cmpl_handler_cont ; 
 scalar_t__ vnic_cq_service (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int fnic_wq_cmpl_handler(struct fnic *fnic, int work_to_do)
{
	unsigned int wq_work_done = 0;
	unsigned int i;

	for (i = 0; i < fnic->raw_wq_count; i++) {
		wq_work_done  += vnic_cq_service(&fnic->cq[fnic->rq_count+i],
						 work_to_do,
						 fnic_wq_cmpl_handler_cont,
						 NULL);
	}

	return wq_work_done;
}