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
 int /*<<< orphan*/  MD_CLUSTER_SEND_LOCKED_ALREADY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_comm (struct md_cluster_info*) ; 

__attribute__((used)) static void add_new_disk_cancel(struct mddev *mddev)
{
	struct md_cluster_info *cinfo = mddev->cluster_info;
	clear_bit(MD_CLUSTER_SEND_LOCKED_ALREADY, &cinfo->state);
	unlock_comm(cinfo);
}