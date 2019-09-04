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
struct TYPE_2__ {int /*<<< orphan*/  rb_root; } ;
struct cfq_rb_root {TYPE_1__ rb; } ;
struct cfq_queue {int dummy; } ;
struct cfq_data {int /*<<< orphan*/  rq_queued; int /*<<< orphan*/  serving_wl_type; int /*<<< orphan*/  serving_wl_class; int /*<<< orphan*/  serving_group; } ;

/* Variables and functions */
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 struct cfq_queue* cfq_rb_first (struct cfq_rb_root*) ; 
 struct cfq_rb_root* st_for (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cfq_queue *cfq_get_next_queue(struct cfq_data *cfqd)
{
	struct cfq_rb_root *st = st_for(cfqd->serving_group,
			cfqd->serving_wl_class, cfqd->serving_wl_type);

	if (!cfqd->rq_queued)
		return NULL;

	/* There is nothing to dispatch */
	if (!st)
		return NULL;
	if (RB_EMPTY_ROOT(&st->rb.rb_root))
		return NULL;
	return cfq_rb_first(st);
}