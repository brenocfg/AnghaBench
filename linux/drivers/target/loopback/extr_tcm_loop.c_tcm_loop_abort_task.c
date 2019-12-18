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
struct tcm_loop_tpg {int dummy; } ;
struct tcm_loop_hba {struct tcm_loop_tpg* tl_hba_tpgs; } ;
struct scsi_cmnd {TYPE_1__* request; TYPE_2__* device; } ;
struct TYPE_4__ {size_t id; int /*<<< orphan*/  lun; int /*<<< orphan*/  host; } ;
struct TYPE_3__ {int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 int /*<<< orphan*/  TMR_ABORT_TASK ; 
 int TMR_FUNCTION_COMPLETE ; 
 scalar_t__ shost_priv (int /*<<< orphan*/ ) ; 
 int tcm_loop_issue_tmr (struct tcm_loop_tpg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcm_loop_abort_task(struct scsi_cmnd *sc)
{
	struct tcm_loop_hba *tl_hba;
	struct tcm_loop_tpg *tl_tpg;
	int ret = FAILED;

	/*
	 * Locate the tcm_loop_hba_t pointer
	 */
	tl_hba = *(struct tcm_loop_hba **)shost_priv(sc->device->host);
	tl_tpg = &tl_hba->tl_hba_tpgs[sc->device->id];
	ret = tcm_loop_issue_tmr(tl_tpg, sc->device->lun,
				 sc->request->tag, TMR_ABORT_TASK);
	return (ret == TMR_FUNCTION_COMPLETE) ? SUCCESS : FAILED;
}