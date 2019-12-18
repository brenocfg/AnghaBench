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
struct siw_cm_work {int type; int /*<<< orphan*/  work; struct siw_cep* cep; } ;
struct siw_cep {scalar_t__ state; scalar_t__ qp; struct siw_cm_work* mpa_timer; } ;
typedef  enum siw_work_type { ____Placeholder_siw_work_type } siw_work_type ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long MPAREP_TIMEOUT ; 
 unsigned long MPAREQ_TIMEOUT ; 
 int SIW_CM_WORK_MPATIMEOUT ; 
 scalar_t__ SIW_EPSTATE_AWAIT_MPAREP ; 
 int qp_id (scalar_t__) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  siw_cep_get (struct siw_cep*) ; 
 int /*<<< orphan*/  siw_cm_work_handler ; 
 int /*<<< orphan*/  siw_cm_wq ; 
 int /*<<< orphan*/  siw_dbg_cep (struct siw_cep*,char*,...) ; 
 struct siw_cm_work* siw_get_work (struct siw_cep*) ; 

int siw_cm_queue_work(struct siw_cep *cep, enum siw_work_type type)
{
	struct siw_cm_work *work = siw_get_work(cep);
	unsigned long delay = 0;

	if (!work) {
		siw_dbg_cep(cep, "failed with no work available\n");
		return -ENOMEM;
	}
	work->type = type;
	work->cep = cep;

	siw_cep_get(cep);

	INIT_DELAYED_WORK(&work->work, siw_cm_work_handler);

	if (type == SIW_CM_WORK_MPATIMEOUT) {
		cep->mpa_timer = work;

		if (cep->state == SIW_EPSTATE_AWAIT_MPAREP)
			delay = MPAREQ_TIMEOUT;
		else
			delay = MPAREP_TIMEOUT;
	}
	siw_dbg_cep(cep, "[QP %u]: work type: %d, timeout %lu\n",
		    cep->qp ? qp_id(cep->qp) : -1, type, delay);

	queue_delayed_work(siw_cm_wq, &work->work, delay);

	return 0;
}