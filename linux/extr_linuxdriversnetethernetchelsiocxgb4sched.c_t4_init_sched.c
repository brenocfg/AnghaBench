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
struct sched_table {unsigned int sched_size; TYPE_1__* tab; int /*<<< orphan*/  rw_lock; } ;
struct sched_class {int dummy; } ;
struct TYPE_2__ {unsigned int idx; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue_list; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCHED_STATE_UNUSED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sched_table* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct sched_table *t4_init_sched(unsigned int sched_size)
{
	struct sched_table *s;
	unsigned int i;

	s = kvzalloc(sizeof(*s) + sched_size * sizeof(struct sched_class), GFP_KERNEL);
	if (!s)
		return NULL;

	s->sched_size = sched_size;
	rwlock_init(&s->rw_lock);

	for (i = 0; i < s->sched_size; i++) {
		memset(&s->tab[i], 0, sizeof(struct sched_class));
		s->tab[i].idx = i;
		s->tab[i].state = SCHED_STATE_UNUSED;
		INIT_LIST_HEAD(&s->tab[i].queue_list);
		spin_lock_init(&s->tab[i].lock);
		atomic_set(&s->tab[i].refcnt, 0);
	}
	return s;
}