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
struct mddev {int ro; int /*<<< orphan*/  sb_flags; } ;
struct raid_set {struct mddev md; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_SB_CHANGE_DEVS ; 
 int /*<<< orphan*/  md_update_sb (struct mddev*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rs_update_sbs(struct raid_set *rs)
{
	struct mddev *mddev = &rs->md;
	int ro = mddev->ro;

	set_bit(MD_SB_CHANGE_DEVS, &mddev->sb_flags);
	mddev->ro = 0;
	md_update_sb(mddev, 1);
	mddev->ro = ro;
}