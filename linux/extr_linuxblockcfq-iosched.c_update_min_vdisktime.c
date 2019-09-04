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
struct TYPE_2__ {int /*<<< orphan*/  rb_leftmost; int /*<<< orphan*/  rb_root; } ;
struct cfq_rb_root {int /*<<< orphan*/  min_vdisktime; TYPE_1__ rb; } ;
struct cfq_group {int /*<<< orphan*/  vdisktime; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max_vdisktime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cfq_group* rb_entry_cfqg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_min_vdisktime(struct cfq_rb_root *st)
{
	if (!RB_EMPTY_ROOT(&st->rb.rb_root)) {
		struct cfq_group *cfqg = rb_entry_cfqg(st->rb.rb_leftmost);

		st->min_vdisktime = max_vdisktime(st->min_vdisktime,
						  cfqg->vdisktime);
	}
}