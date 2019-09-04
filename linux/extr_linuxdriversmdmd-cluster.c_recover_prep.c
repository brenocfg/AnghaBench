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
struct md_cluster_info {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_CLUSTER_SUSPEND_READ_BALANCING ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void recover_prep(void *arg)
{
	struct mddev *mddev = arg;
	struct md_cluster_info *cinfo = mddev->cluster_info;
	set_bit(MD_CLUSTER_SUSPEND_READ_BALANCING, &cinfo->state);
}