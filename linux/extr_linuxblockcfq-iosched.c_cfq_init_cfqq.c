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
struct cfq_queue {int /*<<< orphan*/  pid; struct cfq_data* cfqd; scalar_t__ ref; int /*<<< orphan*/  fifo; int /*<<< orphan*/  p_node; int /*<<< orphan*/  rb_node; } ;
struct cfq_data {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfq_class_idle (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_mark_cfqq_idle_window (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_mark_cfqq_prio_changed (struct cfq_queue*) ; 
 int /*<<< orphan*/  cfq_mark_cfqq_sync (struct cfq_queue*) ; 

__attribute__((used)) static void cfq_init_cfqq(struct cfq_data *cfqd, struct cfq_queue *cfqq,
			  pid_t pid, bool is_sync)
{
	RB_CLEAR_NODE(&cfqq->rb_node);
	RB_CLEAR_NODE(&cfqq->p_node);
	INIT_LIST_HEAD(&cfqq->fifo);

	cfqq->ref = 0;
	cfqq->cfqd = cfqd;

	cfq_mark_cfqq_prio_changed(cfqq);

	if (is_sync) {
		if (!cfq_class_idle(cfqq))
			cfq_mark_cfqq_idle_window(cfqq);
		cfq_mark_cfqq_sync(cfqq);
	}
	cfqq->pid = pid;
}