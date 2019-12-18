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
struct mirror_set {int /*<<< orphan*/  rh; int /*<<< orphan*/  suspend; } ;
struct dm_target {struct mirror_set* private; } ;
struct dm_dirty_log {TYPE_1__* type; } ;
struct TYPE_2__ {scalar_t__ (* resume ) (struct dm_dirty_log*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dm_dirty_log* dm_rh_dirty_log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_rh_start_recovery (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct dm_dirty_log*) ; 

__attribute__((used)) static void mirror_resume(struct dm_target *ti)
{
	struct mirror_set *ms = ti->private;
	struct dm_dirty_log *log = dm_rh_dirty_log(ms->rh);

	atomic_set(&ms->suspend, 0);
	if (log->type->resume && log->type->resume(log))
		/* FIXME: need better error handling */
		DMWARN("log resume failed");
	dm_rh_start_recovery(ms->rh);
}