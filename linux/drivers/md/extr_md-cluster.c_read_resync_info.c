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
struct resync_info {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct mddev {struct md_cluster_info* cluster_info; } ;
struct md_cluster_info {scalar_t__ suspend_lo; scalar_t__ suspend_hi; } ;
struct TYPE_2__ {int /*<<< orphan*/  sb_lvbptr; } ;
struct dlm_lock_resource {TYPE_1__ lksb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_CR ; 
 int /*<<< orphan*/  dlm_lock_sync (struct dlm_lock_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_unlock_sync (struct dlm_lock_resource*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct resync_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int read_resync_info(struct mddev *mddev,
			    struct dlm_lock_resource *lockres)
{
	struct resync_info ri;
	struct md_cluster_info *cinfo = mddev->cluster_info;
	int ret = 0;

	dlm_lock_sync(lockres, DLM_LOCK_CR);
	memcpy(&ri, lockres->lksb.sb_lvbptr, sizeof(struct resync_info));
	if (le64_to_cpu(ri.hi) > 0) {
		cinfo->suspend_hi = le64_to_cpu(ri.hi);
		cinfo->suspend_lo = le64_to_cpu(ri.lo);
		ret = 1;
	}
	dlm_unlock_sync(lockres);
	return ret;
}