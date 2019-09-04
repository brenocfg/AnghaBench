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
struct suspend_info {void* lo; scalar_t__ hi; } ;
struct resync_info {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct mddev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sb_lvbptr; } ;
struct dlm_lock_resource {TYPE_1__ lksb; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_CR ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dlm_lock_sync (struct dlm_lock_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_unlock_sync (struct dlm_lock_resource*) ; 
 struct suspend_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct resync_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct suspend_info *read_resync_info(struct mddev *mddev, struct dlm_lock_resource *lockres)
{
	struct resync_info ri;
	struct suspend_info *s = NULL;
	sector_t hi = 0;

	dlm_lock_sync(lockres, DLM_LOCK_CR);
	memcpy(&ri, lockres->lksb.sb_lvbptr, sizeof(struct resync_info));
	hi = le64_to_cpu(ri.hi);
	if (hi > 0) {
		s = kzalloc(sizeof(struct suspend_info), GFP_KERNEL);
		if (!s)
			goto out;
		s->hi = hi;
		s->lo = le64_to_cpu(ri.lo);
	}
	dlm_unlock_sync(lockres);
out:
	return s;
}