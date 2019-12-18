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
struct TYPE_2__ {scalar_t__ sb_status; } ;
struct dlm_lock_resource {int sync_locking_done; int mode; TYPE_1__ lksb; int /*<<< orphan*/  sync_locking; int /*<<< orphan*/  bast; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; int /*<<< orphan*/  ls; } ;

/* Variables and functions */
 int dlm_lock (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_lock_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_ast ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dlm_lock_sync(struct dlm_lock_resource *res, int mode)
{
	int ret = 0;

	ret = dlm_lock(res->ls, mode, &res->lksb,
			res->flags, res->name, strlen(res->name),
			0, sync_ast, res, res->bast);
	if (ret)
		return ret;
	wait_event(res->sync_locking, res->sync_locking_done);
	res->sync_locking_done = false;
	if (res->lksb.sb_status == 0)
		res->mode = mode;
	return res->lksb.sb_status;
}