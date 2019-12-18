#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dm_snapshot {TYPE_1__* ti; scalar_t__ valid; TYPE_3__* store; } ;
struct TYPE_6__ {TYPE_2__* type; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* drop_snapshot ) (TYPE_3__*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dm_table_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void __invalidate_snapshot(struct dm_snapshot *s, int err)
{
	if (!s->valid)
		return;

	if (err == -EIO)
		DMERR("Invalidating snapshot: Error reading/writing.");
	else if (err == -ENOMEM)
		DMERR("Invalidating snapshot: Unable to allocate exception.");

	if (s->store->type->drop_snapshot)
		s->store->type->drop_snapshot(s->store);

	s->valid = 0;

	dm_table_event(s->ti->table);
}