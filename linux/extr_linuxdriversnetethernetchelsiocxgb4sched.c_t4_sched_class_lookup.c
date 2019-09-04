#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tp ;
struct sched_table {size_t sched_size; struct sched_class* tab; } ;
struct TYPE_5__ {void* class; } ;
struct TYPE_4__ {TYPE_2__ params; } ;
struct ch_sched_params {scalar_t__ type; TYPE_1__ u; } ;
struct sched_class {scalar_t__ state; struct ch_sched_params const info; } ;
struct port_info {struct sched_table* sched_tbl; } ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 void* SCHED_CLS_NONE ; 
 scalar_t__ SCHED_STATE_UNUSED ; 
 int /*<<< orphan*/  memcmp (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memcpy (struct ch_sched_params*,struct ch_sched_params const*,int) ; 

__attribute__((used)) static struct sched_class *t4_sched_class_lookup(struct port_info *pi,
						const struct ch_sched_params *p)
{
	struct sched_table *s = pi->sched_tbl;
	struct sched_class *e, *end;
	struct sched_class *found = NULL;

	if (!p) {
		/* Get any available unused class */
		end = &s->tab[s->sched_size];
		for (e = &s->tab[0]; e != end; ++e) {
			if (e->state == SCHED_STATE_UNUSED) {
				found = e;
				break;
			}
		}
	} else {
		/* Look for a class with matching scheduling parameters */
		struct ch_sched_params info;
		struct ch_sched_params tp;

		memcpy(&tp, p, sizeof(tp));
		/* Don't try to match class parameter */
		tp.u.params.class = SCHED_CLS_NONE;

		end = &s->tab[s->sched_size];
		for (e = &s->tab[0]; e != end; ++e) {
			if (e->state == SCHED_STATE_UNUSED)
				continue;

			memcpy(&info, &e->info, sizeof(info));
			/* Don't try to match class parameter */
			info.u.params.class = SCHED_CLS_NONE;

			if ((info.type == tp.type) &&
			    (!memcmp(&info.u.params, &tp.u.params,
				     sizeof(info.u.params)))) {
				found = e;
				break;
			}
		}
	}

	return found;
}