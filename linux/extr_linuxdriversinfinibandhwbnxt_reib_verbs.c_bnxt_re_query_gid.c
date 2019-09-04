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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u8 ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sgid_tbl; } ;
struct bnxt_re_dev {TYPE_1__ qplib_res; } ;
struct bnxt_qplib_gid {int dummy; } ;

/* Variables and functions */
 int bnxt_qplib_get_sgid (TYPE_1__*,int /*<<< orphan*/ *,int,struct bnxt_qplib_gid*) ; 
 int /*<<< orphan*/  memset (union ib_gid*,int /*<<< orphan*/ ,int) ; 
 struct bnxt_re_dev* to_bnxt_re_dev (struct ib_device*,struct ib_device*) ; 

int bnxt_re_query_gid(struct ib_device *ibdev, u8 port_num,
		      int index, union ib_gid *gid)
{
	struct bnxt_re_dev *rdev = to_bnxt_re_dev(ibdev, ibdev);
	int rc = 0;

	/* Ignore port_num */
	memset(gid, 0, sizeof(*gid));
	rc = bnxt_qplib_get_sgid(&rdev->qplib_res,
				 &rdev->qplib_res.sgid_tbl, index,
				 (struct bnxt_qplib_gid *)gid);
	return rc;
}