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
struct priority_group {int dummy; } ;
struct multipath {int /*<<< orphan*/  pg_init_count; int /*<<< orphan*/  flags; scalar_t__ hw_handler_name; struct priority_group* current_pg; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPATHF_PG_INIT_REQUIRED ; 
 int /*<<< orphan*/  MPATHF_QUEUE_IO ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __switch_pg(struct multipath *m, struct priority_group *pg)
{
	m->current_pg = pg;

	/* Must we initialise the PG first, and queue I/O till it's ready? */
	if (m->hw_handler_name) {
		set_bit(MPATHF_PG_INIT_REQUIRED, &m->flags);
		set_bit(MPATHF_QUEUE_IO, &m->flags);
	} else {
		clear_bit(MPATHF_PG_INIT_REQUIRED, &m->flags);
		clear_bit(MPATHF_QUEUE_IO, &m->flags);
	}

	atomic_set(&m->pg_init_count, 0);
}