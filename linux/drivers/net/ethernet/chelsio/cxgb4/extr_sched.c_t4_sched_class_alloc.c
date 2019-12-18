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
typedef  scalar_t__ u8 ;
struct TYPE_3__ {scalar_t__ class; } ;
struct TYPE_4__ {TYPE_1__ params; } ;
struct ch_sched_params {TYPE_2__ u; } ;
struct sched_class {scalar_t__ idx; int /*<<< orphan*/  state; int /*<<< orphan*/  refcnt; struct ch_sched_params info; } ;
struct port_info {int dummy; } ;
typedef  int /*<<< orphan*/  np ;

/* Variables and functions */
 scalar_t__ SCHED_CLS_NONE ; 
 int /*<<< orphan*/  SCHED_FW_OP_ADD ; 
 int /*<<< orphan*/  SCHED_STATE_ACTIVE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ch_sched_params*,struct ch_sched_params*,int) ; 
 int t4_sched_class_fw_cmd (struct port_info*,struct ch_sched_params*,int /*<<< orphan*/ ) ; 
 struct sched_class* t4_sched_class_lookup (struct port_info*,struct ch_sched_params*) ; 

__attribute__((used)) static struct sched_class *t4_sched_class_alloc(struct port_info *pi,
						struct ch_sched_params *p)
{
	struct sched_class *e;
	u8 class_id;
	int err;

	if (!p)
		return NULL;

	class_id = p->u.params.class;

	/* Only accept search for existing class with matching params
	 * or allocation of new class with specified params
	 */
	if (class_id != SCHED_CLS_NONE)
		return NULL;

	/* See if there's an exisiting class with same
	 * requested sched params
	 */
	e = t4_sched_class_lookup(pi, p);
	if (!e) {
		struct ch_sched_params np;

		/* Fetch any available unused class */
		e = t4_sched_class_lookup(pi, NULL);
		if (!e)
			return NULL;

		memcpy(&np, p, sizeof(np));
		np.u.params.class = e->idx;
		/* New class */
		err = t4_sched_class_fw_cmd(pi, &np, SCHED_FW_OP_ADD);
		if (err)
			return NULL;
		memcpy(&e->info, &np, sizeof(e->info));
		atomic_set(&e->refcnt, 0);
		e->state = SCHED_STATE_ACTIVE;
	}

	return e;
}