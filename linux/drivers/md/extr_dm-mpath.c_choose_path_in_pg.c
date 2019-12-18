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
struct TYPE_4__ {TYPE_1__* type; } ;
struct priority_group {TYPE_2__ ps; } ;
struct pgpath {int dummy; } ;
struct multipath {int /*<<< orphan*/  lock; struct pgpath* current_pgpath; int /*<<< orphan*/  current_pg; } ;
struct dm_path {int dummy; } ;
struct TYPE_3__ {struct dm_path* (* select_path ) (TYPE_2__*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 struct pgpath* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct priority_group* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __switch_pg (struct multipath*,struct priority_group*) ; 
 struct pgpath* path_to_pgpath (struct dm_path*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct dm_path* stub1 (TYPE_2__*,size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct pgpath *choose_path_in_pg(struct multipath *m,
					struct priority_group *pg,
					size_t nr_bytes)
{
	unsigned long flags;
	struct dm_path *path;
	struct pgpath *pgpath;

	path = pg->ps.type->select_path(&pg->ps, nr_bytes);
	if (!path)
		return ERR_PTR(-ENXIO);

	pgpath = path_to_pgpath(path);

	if (unlikely(READ_ONCE(m->current_pg) != pg)) {
		/* Only update current_pgpath if pg changed */
		spin_lock_irqsave(&m->lock, flags);
		m->current_pgpath = pgpath;
		__switch_pg(m, pg);
		spin_unlock_irqrestore(&m->lock, flags);
	}

	return pgpath;
}