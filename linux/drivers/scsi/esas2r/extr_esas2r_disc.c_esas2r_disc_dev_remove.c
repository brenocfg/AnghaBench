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
struct esas2r_target {scalar_t__ new_target_state; } ;
struct esas2r_request {scalar_t__ interrupt_cx; } ;
struct esas2r_disc_context {struct esas2r_target* curr_targ; int /*<<< orphan*/  state; } ;
struct esas2r_adapter {struct esas2r_target* targetdb; struct esas2r_target* targetdb_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCS_DEV_ADD ; 
 scalar_t__ TS_INVALID ; 
 scalar_t__ TS_NOT_PRESENT ; 
 struct esas2r_target* esas2r_targ_db_find_by_virt_id (struct esas2r_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_targ_db_remove (struct esas2r_adapter*,struct esas2r_target*) ; 
 int /*<<< orphan*/  esas2r_targ_get_id (struct esas2r_target*,struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_trace_enter () ; 
 int /*<<< orphan*/  esas2r_trace_exit () ; 

__attribute__((used)) static bool esas2r_disc_dev_remove(struct esas2r_adapter *a,
				   struct esas2r_request *rq)
{
	struct esas2r_disc_context *dc =
		(struct esas2r_disc_context *)rq->interrupt_cx;
	struct esas2r_target *t;
	struct esas2r_target *t2;

	esas2r_trace_enter();

	/* process removals. */

	for (t = a->targetdb; t < a->targetdb_end; t++) {
		if (t->new_target_state != TS_NOT_PRESENT)
			continue;

		t->new_target_state = TS_INVALID;

		/* remove the right target! */

		t2 =
			esas2r_targ_db_find_by_virt_id(a,
						       esas2r_targ_get_id(t,
									  a));

		if (t2)
			esas2r_targ_db_remove(a, t2);
	}

	/* removals complete.  process arrivals. */

	dc->state = DCS_DEV_ADD;
	dc->curr_targ = a->targetdb;

	esas2r_trace_exit();

	return false;
}