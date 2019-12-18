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
struct mddev {struct md_cluster_info* cluster_info; } ;
struct md_cluster_info {int /*<<< orphan*/  resync_lockres; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_EX ; 
 int dlm_lock_sync_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mddev*) ; 

__attribute__((used)) static int resync_start(struct mddev *mddev)
{
	struct md_cluster_info *cinfo = mddev->cluster_info;
	return dlm_lock_sync_interruptible(cinfo->resync_lockres, DLM_LOCK_EX, mddev);
}