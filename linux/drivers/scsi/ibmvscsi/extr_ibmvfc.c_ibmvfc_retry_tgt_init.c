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
struct ibmvfc_target {scalar_t__ init_retries; TYPE_1__* vhost; } ;
struct TYPE_2__ {int /*<<< orphan*/  work_wait_q; } ;

/* Variables and functions */
 scalar_t__ IBMVFC_MAX_TGT_INIT_RETRIES ; 
 int /*<<< orphan*/  IBMVFC_TGT_ACTION_DEL_RPORT ; 
 int /*<<< orphan*/  ibmvfc_init_tgt (struct ibmvfc_target*,void (*) (struct ibmvfc_target*)) ; 
 int /*<<< orphan*/  ibmvfc_set_tgt_action (struct ibmvfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ibmvfc_retry_tgt_init(struct ibmvfc_target *tgt,
				  void (*job_step) (struct ibmvfc_target *))
{
	if (++tgt->init_retries > IBMVFC_MAX_TGT_INIT_RETRIES) {
		ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_DEL_RPORT);
		wake_up(&tgt->vhost->work_wait_q);
		return 0;
	} else
		ibmvfc_init_tgt(tgt, job_step);
	return 1;
}