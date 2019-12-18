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
struct md_cluster_info {int /*<<< orphan*/  newdisk_completion; int /*<<< orphan*/  no_new_dev_lockres; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MD_CLUSTER_WAITING_FOR_NEWDISK ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_unlock_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int new_disk_ack(struct mddev *mddev, bool ack)
{
	struct md_cluster_info *cinfo = mddev->cluster_info;

	if (!test_bit(MD_CLUSTER_WAITING_FOR_NEWDISK, &cinfo->state)) {
		pr_warn("md-cluster(%s): Spurious cluster confirmation\n", mdname(mddev));
		return -EINVAL;
	}

	if (ack)
		dlm_unlock_sync(cinfo->no_new_dev_lockres);
	complete(&cinfo->newdisk_completion);
	return 0;
}