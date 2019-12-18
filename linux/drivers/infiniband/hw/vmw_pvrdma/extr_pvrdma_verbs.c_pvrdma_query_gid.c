#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u8 ;
struct pvrdma_dev {int /*<<< orphan*/ * sgid_tbl; TYPE_2__* dsr; } ;
struct ib_device {int dummy; } ;
struct TYPE_3__ {int gid_tbl_len; } ;
struct TYPE_4__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (union ib_gid*,int /*<<< orphan*/ *,int) ; 
 struct pvrdma_dev* to_vdev (struct ib_device*) ; 

int pvrdma_query_gid(struct ib_device *ibdev, u8 port, int index,
		     union ib_gid *gid)
{
	struct pvrdma_dev *dev = to_vdev(ibdev);

	if (index >= dev->dsr->caps.gid_tbl_len)
		return -EINVAL;

	memcpy(gid, &dev->sgid_tbl[index], sizeof(union ib_gid));

	return 0;
}