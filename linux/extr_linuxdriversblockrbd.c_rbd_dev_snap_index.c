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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {struct ceph_snap_context* snapc; } ;
struct rbd_device {TYPE_1__ header; } ;
struct ceph_snap_context {int /*<<< orphan*/ * snaps; int /*<<< orphan*/  num_snaps; } ;
typedef  int /*<<< orphan*/  snap_id ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_SNAP_INDEX ; 
 int /*<<< orphan*/ * bsearch (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snapid_compare_reverse ; 

__attribute__((used)) static u32 rbd_dev_snap_index(struct rbd_device *rbd_dev, u64 snap_id)
{
	struct ceph_snap_context *snapc = rbd_dev->header.snapc;
	u64 *found;

	found = bsearch(&snap_id, &snapc->snaps, snapc->num_snaps,
				sizeof (snap_id), snapid_compare_reverse);

	return found ? (u32)(found - &snapc->snaps[0]) : BAD_SNAP_INDEX;
}