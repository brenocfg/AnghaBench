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
struct TYPE_2__ {int nodes; } ;
struct mddev {scalar_t__ recovery_cp; TYPE_1__ bitmap_info; struct md_cluster_info* cluster_info; } ;
struct md_rdev {int /*<<< orphan*/  desc_nr; struct mddev* mddev; } ;
struct md_cluster_info {int slot_number; } ;
struct cluster_msg {void* raid_slot; void* type; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  RE_ADD ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int md_bitmap_copy_from_slot (struct mddev*,int,scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int sendmsg (struct md_cluster_info*,struct cluster_msg*,int) ; 

__attribute__((used)) static int gather_bitmaps(struct md_rdev *rdev)
{
	int sn, err;
	sector_t lo, hi;
	struct cluster_msg cmsg = {0};
	struct mddev *mddev = rdev->mddev;
	struct md_cluster_info *cinfo = mddev->cluster_info;

	cmsg.type = cpu_to_le32(RE_ADD);
	cmsg.raid_slot = cpu_to_le32(rdev->desc_nr);
	err = sendmsg(cinfo, &cmsg, 1);
	if (err)
		goto out;

	for (sn = 0; sn < mddev->bitmap_info.nodes; sn++) {
		if (sn == (cinfo->slot_number - 1))
			continue;
		err = md_bitmap_copy_from_slot(mddev, sn, &lo, &hi, false);
		if (err) {
			pr_warn("md-cluster: Could not gather bitmaps from slot %d", sn);
			goto out;
		}
		if ((hi > 0) && (lo < mddev->recovery_cp))
			mddev->recovery_cp = lo;
	}
out:
	return err;
}