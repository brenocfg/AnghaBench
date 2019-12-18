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
struct md_rdev {int /*<<< orphan*/  desc_nr; } ;
struct md_cluster_info {int dummy; } ;
struct cluster_msg {void* raid_slot; void* type; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  REMOVE ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int sendmsg (struct md_cluster_info*,struct cluster_msg*,int) ; 

__attribute__((used)) static int remove_disk(struct mddev *mddev, struct md_rdev *rdev)
{
	struct cluster_msg cmsg = {0};
	struct md_cluster_info *cinfo = mddev->cluster_info;
	cmsg.type = cpu_to_le32(REMOVE);
	cmsg.raid_slot = cpu_to_le32(rdev->desc_nr);
	return sendmsg(cinfo, &cmsg, 1);
}