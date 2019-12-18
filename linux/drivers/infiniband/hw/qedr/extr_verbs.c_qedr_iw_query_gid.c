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
struct TYPE_4__ {int /*<<< orphan*/  subnet_prefix; int /*<<< orphan*/  interface_id; } ;
union ib_gid {TYPE_2__ global; int /*<<< orphan*/  raw; } ;
typedef  int /*<<< orphan*/  u8 ;
struct qedr_dev {TYPE_1__* ndev; } ;
struct ib_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDR_MSG_INIT ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qedr_dev* get_qedr_dev (struct ib_device*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int qedr_iw_query_gid(struct ib_device *ibdev, u8 port,
		      int index, union ib_gid *sgid)
{
	struct qedr_dev *dev = get_qedr_dev(ibdev);

	memset(sgid->raw, 0, sizeof(sgid->raw));
	ether_addr_copy(sgid->raw, dev->ndev->dev_addr);

	DP_DEBUG(dev, QEDR_MSG_INIT, "QUERY sgid[%d]=%llx:%llx\n", index,
		 sgid->global.interface_id, sgid->global.subnet_prefix);

	return 0;
}