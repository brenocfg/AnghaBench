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
struct bfa_ioim_s {TYPE_1__* fcpim; int /*<<< orphan*/  qe; int /*<<< orphan*/  io_cbfn; int /*<<< orphan*/  hcb_qe; int /*<<< orphan*/  bfa; int /*<<< orphan*/  itnim; } ;
typedef  scalar_t__ bfa_boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  ioim_comp_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bfa_cb_ioim_failed ; 
 int /*<<< orphan*/  __bfa_cb_ioim_pathtov ; 
 int /*<<< orphan*/  bfa_cb_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_ioim_s*) ; 
 int /*<<< orphan*/  bfa_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iocom_nexus_abort ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void
bfa_ioim_delayed_comp(struct bfa_ioim_s *ioim, bfa_boolean_t iotov)
{
	/*
	 * If path tov timer expired, failback with PATHTOV status - these
	 * IO requests are not normally retried by IO stack.
	 *
	 * Otherwise device cameback online and fail it with normal failed
	 * status so that IO stack retries these failed IO requests.
	 */
	if (iotov)
		ioim->io_cbfn = __bfa_cb_ioim_pathtov;
	else {
		ioim->io_cbfn = __bfa_cb_ioim_failed;
		bfa_stats(ioim->itnim, iocom_nexus_abort);
	}
	bfa_cb_queue(ioim->bfa, &ioim->hcb_qe, ioim->io_cbfn, ioim);

	/*
	 * Move IO to fcpim global queue since itnim will be
	 * freed.
	 */
	list_del(&ioim->qe);
	list_add_tail(&ioim->qe, &ioim->fcpim->ioim_comp_q);
}